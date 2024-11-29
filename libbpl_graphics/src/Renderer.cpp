//
// Created by Bradley Remedios on 10/25/24.
//

#include <bpl/graphics/Renderer.h>

#include <iostream>

#include <bpl/graphics/Window.h>

namespace bpl::graphics {
    Renderer::Renderer() {

    }

    Renderer::~Renderer() {
        Destroy();
    }

    bool Renderer::Create(WindowPtr window) {
        m_window = window;
        m_renderer = SDL_CreateRenderer(window->getSdlWindow(), -1, SDL_RENDERER_ACCELERATED);

        if (nullptr == m_renderer) {
            std::cerr << "SDL_CreateRenderer failed.  SDL_ERROR: " << SDL_GetError() << std::endl;

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

} // bpl::graphics