//
// Created by Bradley Rmedios on 11/29/24.
//
#include <iostream>
#include <thread>

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

#include <bpl/graphics/Window.h>
#include <bpl/graphics/Renderer.h>
#include <bpl/graphics/EventLoop.h>

int main() {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        std::cerr << "SDL_Init failed: " << SDL_GetError() << std::endl;

        return -1;
    }

    if (TTF_Init() < 0) {
        std::cerr << "TTF_Init failed: " << SDL_GetError() << std::endl;

        SDL_Quit();
        return -1;
    }

    bpl::graphics::WindowPtr window = bpl::graphics::Window::CreateInstance("Hello World", 720, 720, false);

    if (!window->isValid()) {
        std::cerr << "Failed to create window" << std::endl;

        TTF_Quit();
        SDL_Quit();
    }

    bpl::graphics::RendererPtr renderer = bpl::graphics::Renderer::CreateInstance(window);

    if (!renderer->isValid()) {
        std::cerr << "Failed to create renderer" << std::endl;

        TTF_Quit();
        SDL_Quit();
    }

    bpl::graphics::EventLoopPtr loop = std::make_shared<bpl::graphics::EventLoop>();

    loop->setFramerate(30);
    loop->setRenderer(renderer);
    loop->Run();

    TTF_Quit();
    SDL_Quit();

} // main