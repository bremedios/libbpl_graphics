//
// Created by Bradley Remedios on 10/25/24.
//

#ifndef BPL_GRAPHICS_FONT_H
#define BPL_GRAPHICS_FONT_H

#include <memory>
#include <string>

#include <SDL2/SDL_ttf.h>

#include <bpl/graphics/Surface.h>
#include <bpl/graphics/Renderer.h>

namespace bpl::graphics {

    class Font {
    public:
        enum Alignment {
            Left,
            Right,
            Center,
            Top,
            Bottom
        };
        Font(const std::string& name, int size);
        virtual ~Font();

        bool Load();
        void Release();
        bool isValid() { return m_font != nullptr; }

        bool Render(
            graphics::RendererPtr renderer,
            SDL_Color color,
            const std::string & text,
            const SDL_Rect& dest,
            Alignment halignment=Alignment::Left,
            Alignment valignment=Alignment::Top);
    private:
        std::string m_fontName;
        int m_fontSize;
        TTF_Font*   m_font=nullptr;
    };

    typedef std::shared_ptr<Font> FontPtr;
} // bpl::graphics

#endif //BPL_GRAPHICS_FONT_H