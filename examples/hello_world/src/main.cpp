//
// Created by Bradley Rmedios on 11/29/24.
//
#include <iostream>
#include <thread>

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

#include <bpl/graphics/Window.h>
#include <bpl/graphics/Renderer.h>
#include <bpl/graphics/RenderObject.h>
#include <bpl/graphics/EventLoop.h>
#include <bpl/graphics/Font.h>
#include <bpl/graphics/FontCache.h>

class MyWindow : public bpl::graphics::RenderObject {
public:
    MyWindow() = default;
    ~MyWindow() override {};

    void Render(bpl::graphics::RendererPtr renderer) override {
        auto font = bpl::graphics::FontCache::getInstance()->getFont("/usr/share/fonts/truetype/ubuntu/UbuntuMono-R.ttf", 24);

        if (nullptr == font.get()) {
            std::cerr << "Failed to load font, Cannot render" << std::endl;
            return;
        }
        SDL_Color color = {255, 255, 255};
        SDL_Rect dest = {0,0,720,720};

        if (!font->Render(renderer, color, "Hello World!", dest, bpl::graphics::Font::Alignment:: Center, bpl::graphics::Font::Alignment::Center))
        {
            std::cerr << "Failed to render!" << std::endl;
        }
    }
};// MyWindow

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

    bpl::graphics::RenderObjectPtr renderObj(new MyWindow());

    do {
        bpl::graphics::WindowPtr window = bpl::graphics::Window::CreateInstance("Hello World", 720, 720, false);

        if (!window->isValid()) {
            std::cerr << "Failed to create window" << std::endl;

            break;
        }

        bpl::graphics::RendererPtr renderer = bpl::graphics::Renderer::CreateInstance(window);

        if (!renderer->isValid()) {
            std::cerr << "Failed to create renderer" << std::endl;

            break;
        }

        bpl::graphics::EventLoopPtr loop = std::make_shared<bpl::graphics::EventLoop>();

        loop->setFramerate(30);
        loop->setRenderer(renderer);
        loop->addRenderObject(renderObj);
        loop->Run();

    } while (false);

    bpl::graphics::FontCache::getInstance()->Clear();

    TTF_Quit();
    SDL_Quit();

} // main