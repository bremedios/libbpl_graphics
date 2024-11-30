//
// Created by Bradley Remedios on 10/25/24.
//
#include <iostream>

#include <bpl/graphics/Texture.h>

#include "Debug.h"

namespace bpl::graphics {

    Texture::Texture() {

    } // Texture

    Texture::~Texture() {
        Destroy();
    }

    bool Texture::Create(RendererPtr renderer, SurfacePtr surface, bool destroySurface) {
        m_texture = SDL_CreateTextureFromSurface(renderer->getSdlRenderer(), surface->getSdlSurface());

        if (nullptr == m_texture) {
            ERROR_MSG("SDL_CreateTextureFromSurface Failed. SDL_ERROR: " << SDL_GetError());

            if (destroySurface) {
                surface->Destroy();
            }

            return false;
        }

        if (0 > SDL_QueryTexture(m_texture, nullptr, nullptr, &m_width, &m_height)) {
            ERROR_MSG("SDL_QueryTexture Query Failed. SDL_ERROR: " << SDL_GetError());

            return false;
        }

        if (destroySurface) {
            surface->Destroy();
        }

        return true;
    } // Create

    void Texture::Destroy() {
        if (nullptr != m_texture) {
            SDL_DestroyTexture(m_texture);
            m_texture = nullptr;
        }
    }
    void Texture::GetRect(SDL_Rect &rect) {
        rect.x = 0;
        rect.y = 0;
        rect.w = m_width;
        rect.h = m_height;
    } // GetRect

} // bpl::graphics