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

} // bpl::graphics