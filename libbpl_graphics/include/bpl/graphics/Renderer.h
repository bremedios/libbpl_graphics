//
// Created by Bradley Remedios on 10/25/24.
//

#ifndef BPL_GRAPHICS_RENDERER_H
#define BPL_GRAPHICS_RENDERER_H
#include <memory>
#include <SDL2/SDL_render.h>

#include <bpl/graphics/Window.h>

namespace bpl::graphics {

    class Renderer {
    public:
        Renderer();
        virtual ~Renderer();

        [[nodiscard]] static std::shared_ptr<Renderer> CreateInstance(WindowPtr window);
        [[nodiscard]] bool Create(WindowPtr window);

        bool Destroy();

        [[nodiscard]] SDL_Renderer* getSdlRenderer() { return m_renderer; }
        [[nodiscard]] WindowPtr getWindow() { return m_window; }
        [[nodiscard]] bool isValid() { return m_renderer != nullptr; }

        void RenderClear();
        void RenderPresent();

        bool SetDrawColor(SDL_Color color);
        bool SetDrawColor(int red, int green, int blue, int alpha);

    private:
        SDL_Renderer*     m_renderer = nullptr;
        WindowPtr         m_window;
    }; // class Renderer

    typedef std::shared_ptr<Renderer> RendererPtr;
} // bpl::graphics

#endif //BPL_GRAPHICS_RENDERER_H