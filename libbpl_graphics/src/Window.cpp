//
// Created by Bradley Remedios on 10/25/24.
//

#include <iostream>
#include <bpl/graphics/Window.h>

#include "Debug.h"

namespace bpl::graphics {
    Window::~Window() {

    }

    std::shared_ptr<Window> Window::CreateInstance(const std::string& title, int width, int height, bool fullscreen) {
        WindowPtr window = std::make_shared<Window>();

        if (!window->Create(title, width, height, fullscreen)) {
            ERROR_MSG("Failed to create window");

            window.reset();

            return window;
        }

        return window;
    } // CreateInstance

    bool Window::Create(const std::string& title, int width, int height, bool fullscreen) {
        m_title = title;
        m_width = width;
        m_height = height;
        fullscreen;

        Uint64 flags = SDL_WINDOW_SHOWN;

        if (fullscreen) {
            flags |= SDL_WINDOW_FULLSCREEN;
        }

        m_window = SDL_CreateWindow(title.c_str(), SDL_WINDOWPOS_UNDEFINED,SDL_WINDOWPOS_UNDEFINED, width, height, flags);

        if (nullptr == m_window) {
            ERROR_MSG("SDL_CreateWindow Failed. SDL_ERROR: " << SDL_GetError());

            return false;
        }

        return true;
    } // Create

    void Window::Update() const {
        if (0 > SDL_UpdateWindowSurface(m_window)) {
            std::cerr << "SDL_UpdateWindowSurface Failed.  SDL_ERROR: " << SDL_GetError() << std::endl;
        }
    } // Update
} // gpl::graphics