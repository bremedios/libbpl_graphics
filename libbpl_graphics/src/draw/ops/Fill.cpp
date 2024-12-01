//
// Created by Bradley Remedios on 11/14/24.
//


#include <iostream>

#include <bpl/storage/Json.h>

#include <bpl/graphics/draw/ops/Fill.h>

#include "../../Debug.h"

namespace bpl::graphics::draw::ops {
    Fill::Fill() {
        m_type = "fill";
    }

    bool Fill::Load(bpl::graphics::RendererPtr& renderer, const rapidjson::Value& layout) {
        SDL_Color   color;
        SDL_Rect    rect;

        if (!bpl::graphics::draw::ops::Op::Load(renderer, layout)) {
            ERROR_MSG("Op::Load() failed");

            return false;
        }

        if (!bpl::storage::Json::Load(layout, "color", m_bg)) {
            ERROR_MSG("Failed to get fill color");

            return false;
        }

        if (bpl::storage::Json::Load(layout, "dest", m_destRect)) {
            m_isFullscreen = false;
        }
        else
        {
            m_isFullscreen = true;
        }

        return true;
    } // Load

    bool Fill::Render(graphics::RendererPtr& renderer) {
        if (!m_visible) {
            return true;
        }

        if (!renderer->SetDrawColor(m_bg)) {
            ERROR_MSG("Renderer::SetDrawColor() failed.");

            return false;
        }

        if (m_isFullscreen) {
            if (0 > SDL_RenderFillRect(renderer->getSdlRenderer(), nullptr)) {
                ERROR_MSG("SDL_RenderFillRect failed..  SDL_ERROR:" << SDL_GetError());

                return false;
            }
        } else {
            if (0 > SDL_RenderFillRect(renderer->getSdlRenderer(), &m_destRect)) {
                ERROR_MSG("SDL_RenderFillRect failed.  SDL_ERROR:" << SDL_GetError());

                return false;
            }
        }

        return true;
    } // Render

    void Fill::setColor(int red, int green, int blue) {
        m_bg.r = red;
        m_bg.g = green;
        m_bg.b = blue;
        m_bg.a = 255;
    }

    void Fill::setFullscreen(bool value) {
        m_isFullscreen = value;
    }

    void Fill::setRegion(int x, int y, int width, int height) {
        m_destRect.x = x;
        m_destRect.y = y;
        m_destRect.w = width;
        m_destRect.h = height;
        m_isFullscreen = false;
    }
} // bpl::graphics::draw::ops