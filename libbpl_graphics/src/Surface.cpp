//
// Created by Bradley Remedios on 10/25/24.
//
#include <iostream>

#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>

#include <bpl/graphics/Surface.h>

#include "Debug.h"

namespace bpl::graphics {

    Surface::Surface() {
    } // Surface

    Surface::Surface(SDL_Surface* surface) {
        m_surface = surface;
    }

    Surface::~Surface() {
        Destroy();
    } // ~Surface

    bool Surface::CreateFromImage(const std::string &filename) {
        m_surface = IMG_Load(filename.c_str());

        if (nullptr == m_surface) {
            ERROR_MSG("IMG_Load(" << filename << ") Failed to load image: " << SDL_GetError());

            return false;
        }

        return true;
    } // CreateFromImage

    bool Surface::Create(WindowPtr window) {
        m_surface = SDL_GetWindowSurface(window->getSdlWindow());

        if (nullptr == m_surface) {
            ERROR_MSG("SDL_GetWindowSurface() Failed.  SDL_ERROR: " << SDL_GetError());

            return false;
        }

        return true;
    } // Create

    bool Surface::Create(SDL_Surface* surface) {
        m_surface = surface;

        return true;
    } // Create

    bool Surface::Destroy(){
        SDL_FreeSurface(m_surface);

        m_surface = nullptr;

        return true;
    } // Destroy

} // bpl::graphics