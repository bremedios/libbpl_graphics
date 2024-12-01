//
// Created by Bradley Remedios on 10/25/24.
//

#include <bpl/graphics/Renderer.h>

#include <iostream>

#include <bpl/graphics/Window.h>

#include "Debug.h"

namespace bpl::graphics {
    Renderer::Renderer() {

    }

    Renderer::~Renderer() {
        Destroy();
    }

    RendererPtr Renderer::CreateInstance(WindowPtr window) {
        RendererPtr renderer = std::make_shared<Renderer>();

        if (!renderer->Create(window)) {
            ERROR_MSG("Failed to Create Renderer");

            return renderer;
        }

        return renderer;
    } // CreateInstance

    bool Renderer::Create(WindowPtr window) {
        m_window = window;
        m_renderer = SDL_CreateRenderer(window->getSdlWindow(), -1, SDL_RENDERER_ACCELERATED);

        if (nullptr == m_renderer) {
            ERROR_MSG("SDL_CreateRenderer failed.  SDL_ERROR: " << SDL_GetError());

            return false;
        }

        return true;
    } // Create

    bool Renderer::Destroy () {
        if (nullptr != m_renderer) {
            SDL_DestroyRenderer(m_renderer);

            m_renderer = nullptr;
        }

        return true;
    } // Destory

    void Renderer::RenderClear() {
        SDL_RenderClear(m_renderer);
    }

    void Renderer::RenderPresent() {
        SDL_RenderPresent(m_renderer);
    }

    bool Renderer::SetDrawColor(SDL_Color color) {
        return SetDrawColor(color.r, color.g, color.g, color.a);
    } // SetDrawColor

    bool Renderer::SetDrawColor(int red, int green, int blue, int alpha) {
        if (0 > SDL_SetRenderDrawColor(m_renderer, red, blue, green, alpha)) {
            ERROR_MSG("SDL_SetRenderDrawColor() failed.  SDL_ERROR: " << SDL_GetError());

            return false;
        }

        return true;
    } // SetDrawColor

} // bpl::graphics