//
// Created by Bradley Remedios on 10/26/24.
//
#include <iostream>
#include <fstream>

#include  "nlohmann/json.hpp"

#include <bpl/graphics/Sprite.h>
#include <bpl/graphics/Renderer.h>
#include "Debug.h"

//#define DEBUG_COLLIDERS 1

namespace bpl::graphics {
    Sprite::Sprite(bpl::graphics::RendererPtr& renderer, int systemFramerate)
        : m_renderer(renderer)
        , m_systemFrameRate(systemFramerate){
    }

    Sprite::~Sprite() {

    }

    const std::list<SDL_Rect> &Sprite::GetColliders() const {
        // colliders are stored relative to the image, but they need to be reported relative to teh scene
        return m_globalColliders;
    } // GetColliders

    const SDL_Rect &Sprite::GetCollider() const {
        return m_globalColliderRect;
    }

    void Sprite::FlipNone() {
        m_flip = SDL_FLIP_NONE;
    }

    void Sprite::FlipVertical() {
        m_flip = SDL_FLIP_VERTICAL;
    }

    void Sprite::FlipHorizontal() {
        m_flip = SDL_FLIP_HORIZONTAL;
    }

    bool Sprite::Load(const std::string &filename) {
        m_filename = filename;

        nlohmann::json json_data;

        std::ifstream f(filename);

        if (!f.good()) {
            ERROR_MSG("Failed to open file " << filename);

            return false;
        }

        try {
            json_data = nlohmann::json::parse(f);
        }
        catch(nlohmann::json::exception& e) {
            ERROR_MSG("Unable to load sprite, json::parse(" << filename << ") failed: " << e.what());

            return false;
        }

        m_name = json_data["name"].get<std::string>();

        // Walking speed is not always set.
        try {
            m_walkSpeed = json_data["walk-speed"].get<int>();
        } catch (nlohmann::json::exception& e) {
            m_walkSpeed = 0;
        }

        // Jump speed is not always set.
        try {
            m_jumpSpeed = json_data["jump-speed"].get<int>();
        } catch (nlohmann::json::exception& e) {
            m_jumpSpeed = 0;
        }

        //
        //  Load image
        //
        try {
            m_srcRect.x = json_data["image"][0].get<int>();
            m_srcRect.y = json_data["image"][1].get<int>();
            m_srcRect.w = json_data["image"][2].get<int>();
            m_srcRect.h = json_data["image"][3].get<int>();
        } catch (nlohmann::json::exception& e) {
            ERROR_MSG("No image dimensions set: " << filename);
            return false;
        }

        // Floor should default to image height if not set.
        try {
            m_floor = m_rawFloor = json_data["floor"].get<int>();
        } catch (nlohmann::json::exception& e) {
            m_floor = m_rawFloor = m_srcRect.h;
        }

        //
        //  Load single collider.
        //
        try {
            m_rawColliderRect.x = json_data["collider"][0].get<int>();
            m_rawColliderRect.y = json_data["collider"][1].get<int>();
            m_rawColliderRect.w = json_data["collider"][2].get<int>();
            m_rawColliderRect.h = json_data["collider"][3].get<int>();
        } catch (nlohmann::json::exception& e) {
            //
            //  If there is no collider set, we default to the full image.
            //
            m_rawColliderRect = m_srcRect;
        }

        //
        //  Load colliders
        //
        try {
            for (auto it = json_data["colliders"].begin(); it != json_data["colliders"].end(); it++) {
                SDL_Rect cRect;

                cRect.x = (*it)[0];
                cRect.y = (*it)[1];
                cRect.w = (*it)[2];
                cRect.h = (*it)[3];

                m_rawColliders.push_back(cRect);
            }
        } catch (nlohmann::json::exception& e) {
            m_rawColliders.push_back(m_rawColliderRect);
        }

        //
        //  If we do not have a collider list, we just make it a list of 1.
        //
        if (m_rawColliders.size() == 0) {
            m_rawColliders.push_back(m_rawColliderRect);
        }

        m_framerate = json_data["framerate"].get<int>();
        std::string path = json_data["path"].get<std::string>();


        if ((0 == m_framerate) || (m_systemFrameRate <= m_framerate)) {
            m_framecount = 1;
        }
        else {
            m_framecount = m_systemFrameRate / m_framerate;
        }

        std::list<std::string> sprites = json_data["sprites"].template get <std::list<std::string>>();

        //
        //  Load sprites
        //
        for (std::list<std::string>::iterator it = sprites.begin(); it != sprites.end(); it++) {
            SurfacePtr surface (new Surface);

            if (!surface->CreateFromImage(path + "/" + *it)) {
                ERROR_MSG("Failed to create surface from Image" << *it);
                return false;
            }

            TexturePtr texture(new Texture());

            //
            //  This will destroy the surface once it has been created.
            //
            if (!texture->Create(m_renderer, surface, true)) {
                ERROR_MSG("Texture::Create() failed");

                return false;
            }

            m_textures.push_back(texture);
        }

        m_currentFrame = 0;
        m_currentTexture = m_textures.begin();

        DEBUG_MSG("Loaded Sprite" << filename);

        return true;
    } // Load

    int Sprite::getWalkSpeed() {
        return m_walkSpeed;
    }

    void Sprite::ScaleToHeight(int height) {
        Scale((float)height / (float)m_srcRect.h);
    } // ScaleToHeight

    void Sprite::Scale(float scale) {
        m_scale = scale;
        m_destRect.w = m_srcRect.w * scale;
        m_destRect.h = m_srcRect.h * scale;

        m_colliderRect.x = m_rawColliderRect.x * scale;
        m_colliderRect.y = m_rawColliderRect.y * scale;
        m_colliderRect.w = m_rawColliderRect.w * scale;
        m_colliderRect.h = m_rawColliderRect.h * scale;

        m_colliders.clear();

        for (auto it = m_rawColliders.begin(); it != m_rawColliders.end(); it++) {
            SDL_Rect collider;

            collider.x = it->x * scale;
            collider.y = it->y * scale;
            collider.w = it->w * scale;
            collider.h = it->h * scale;

            m_colliders.push_back(collider);
        }

        UpdateGlobalColliders_();


        m_floor = m_rawFloor*scale;
    } // Scale

    void Sprite::setLoop(bool loop) {
        m_loop = loop;
    }

    void Sprite::setFramerate(int framerate) {
        m_framerate = framerate;

        if ((0 == m_framerate) || (m_systemFrameRate <= m_framerate)) {
            m_framecount = 1;
        }
        else {
            m_framecount = m_systemFrameRate / m_framerate;
        }
    }


    void Sprite::Draw() {
        SDL_Rect dstRect;
        SDL_Rect srcRect;

        //
        //  If we are at the end of the textures we start over.
        //
        if (m_currentTexture == m_textures.end()) {
            m_currentTexture = m_textures.begin();
            m_currentFrame = 0;
        }

        (*m_currentTexture)->GetRect(dstRect);

        if (0 > SDL_RenderCopyEx(m_renderer->getSdlRenderer(), (*m_currentTexture)->getSdlTexture(), &m_srcRect, &m_destRect, 0, nullptr, m_flip)) {
            ERROR_MSG("SDL_RenderCopy() failed.  SDL_ERROR: " << SDL_GetError());
        }

        //
        //  m_currentFrame and m_framecount is for how long a single texture will show on the screen
        //
        if (++m_currentFrame >= m_framecount) {
            ++m_currentTexture;

            //
            //  If we are not looping, ensure that we do not go past the end.
            //
            if ((!m_loop) && (m_currentTexture == m_textures.end())) {
                --m_currentTexture;
            }

            m_currentFrame  = 0;
        }
    }

    void Sprite::DrawCollider(int r, int g, int b) {
        if (0 > SDL_SetRenderDrawColor(m_renderer->getSdlRenderer(), r, g, b, 0)) {
            ERROR_MSG("SDL_SetRenderDrawColor failed.  SDL_ERROR: " << SDL_GetError());

        }

        SDL_Rect rect = m_globalColliderRect;

        if (0 > SDL_RenderDrawRect(m_renderer->getSdlRenderer(), &rect)) {
            ERROR_MSG("SDL_RenderDrawRect failed.  SDL_ERROR:" << SDL_GetError());
        }
    } // DrawCollider

    void Sprite::DrawColliders(int r, int g, int b) {
        if (0 > SDL_SetRenderDrawColor(m_renderer->getSdlRenderer(), r, g, b, 0)) {
            ERROR_MSG("SDL_SetRenderDrawColor failed.  SDL_ERROR: " << SDL_GetError());
        }

        for (auto it = m_globalColliders.begin(); it != m_globalColliders.end(); it++) {
            if (0 > SDL_RenderDrawRect(m_renderer->getSdlRenderer(), &(*it))) {
                ERROR_MSG("SDL_RenderDrawRect failed.  SDL_ERROR:" << SDL_GetError());
            }
        }
    } // DrawColliders

    void Sprite::setPosition(int x, int y) {
        m_destRect.x = x;
        m_destRect.y = y;
        UpdateGlobalColliders_();
    }

    void Sprite::UpdateGlobalColliders_() {
        m_globalColliders.clear();

        //
        //  WARNING: m_srcRect is not scaled.
        //

        //
        //  Flipping does not affect width or height
        //
        m_globalColliderRect.w = m_colliderRect.w;
        m_globalColliderRect.h = m_colliderRect.h;

        switch (m_flip) {
            case SDL_FLIP_NONE:
                m_globalColliderRect.x = m_colliderRect.x + m_destRect.x;
                m_globalColliderRect.y = m_colliderRect.y + m_destRect.y;

                for (auto it = m_colliders.begin(); it != m_colliders.end(); it++) {
                    SDL_Rect collider = *it;

                    collider.x = collider.x + m_destRect.x;
                    collider.y = collider.y + m_destRect.y;

                    m_globalColliders.push_back(collider);
                }
            break;
            case SDL_FLIP_HORIZONTAL:
                //
                //  m_colliderRect is relative to the loaded graphic (0,0)
                //  m_srcRect is relative to image (0,0) and is what part of the graphic will be painted.
                //
                m_globalColliderRect.x = m_destRect.x + (m_srcRect.w * m_scale) - (m_colliderRect.w + m_colliderRect.x);
                m_globalColliderRect.y = m_colliderRect.y + m_destRect.y;

#if defined(DEBUG_COLLIDERS)
                std::cout << "Collider Math (" << m_name << ")" << std::endl;
                std::cout << "    Image: (" << m_srcRect.x << ", " << m_srcRect.y << ") (" << m_srcRect.w << "x" << m_srcRect.h << ")" << std::endl;
                std::cout << "    Destination: (" << m_destRect.x << ", " << m_destRect.y << ") (" << m_destRect.w << "x" << m_destRect.h << ")" << std::endl;
#endif // DEBUG_COLLIDERS

                for (auto it = m_colliders.begin(); it != m_colliders.end(); it++) {
                    SDL_Rect collider = *it;

                    collider.x = m_destRect.x + (m_scale * m_srcRect.w) - (collider.w + collider.x);
                    collider.y = collider.y + m_destRect.y;

                    m_globalColliders.push_back(collider);

#if defined(DEBUG_COLLIDERS)
                    std::cout << "    Local Collider: (" << it->x << ", " << it->y << ") (" << it->w << "x" << it->h << ")" << std::endl;
                    std::cout << "    No Flip Collider: (" << it->x + m_destRect.x << ", " << it->y + m_destRect.y << ") (" << it->w << "x" << it->h << ")" << std::endl;
                    std::cout << "    Global Collider: (" << collider.x << ", " << collider.y << ") (" << collider.w << "x" << collider.h << ")" << std::endl;
#endif // DEBUG_COLLIDERS
                }
                break;
            case SDL_FLIP_VERTICAL:
                ERROR_MSG("Vertical flip not implemented.");
        }
    } // UpdateGlobalColliders_

    void Sprite::getPosition(int &x, int &y) {
        x = m_destRect.x;
        y = m_destRect.y;
    }

    const std::string& Sprite::getName() const {
        return m_name;
    }

    int Sprite::getHeight() {
        return m_destRect.h;
    }

    int Sprite::getWidth() {
        return m_destRect.w;
    }

    int Sprite::getFloor() {
        return m_floor;
    }

} // graphics