//
// Created by Bradley Remedios on 10/25/24.
//

#ifndef BPL_GRAPHICS_WINDOW_H
#define BPL_GRAPHICS_WINDOW_H
#include <memory>

#include <SDL2/SDL.h>

namespace bpl::graphics {
    class Window {
    public:
        Window() = default;
        virtual ~Window();

        [[nodiscard]] static std::shared_ptr<Window> CreateInstance(const std::string& title, int width=-1, int height=-1, bool fullscreen=true);
        [[nodiscard]] bool Create(const std::string& title, int width=-1, int height=-1, bool fullscreen=true);

        void Update() const;

        [[nodiscard]] SDL_Window* getSdlWindow() { return m_window; }
        [[nodiscard]] int getWidth() { return m_width; }
        [[nodiscard]] int getHeight() { return m_height; }
        [[nodiscard]] const std::string& getTitle() { return m_title; }
        [[nodiscard]] bool isFullscreen() { return m_isFullscreen; }
        [[nodiscard]] bool isValid() { return nullptr != m_window; }

    private:

        std::string    m_title;
        int            m_width         = 1280;
        int            m_height        = 720;
        bool           m_isFullscreen  = false;
        SDL_Window*    m_window        = nullptr;
    };

    typedef std::shared_ptr<Window> WindowPtr;
} // graphics

#endif // BPL_GRAPHICS_WINDOW_H