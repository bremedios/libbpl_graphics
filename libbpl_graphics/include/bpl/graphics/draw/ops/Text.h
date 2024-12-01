//
// Created by Bradley Remedios on 11/14/24.
//

#ifndef BPL_GRAPHICS_DRAW_OPS_FONT_H
#define BPL_GRAPHICS_DRAW_OPS_FONT_H

#include <rapidjson/document.h>
#include <SDL2/SDL.h>
#include <bpl/graphics/Font.h>

#include <bpl/graphics/draw/ops/Op.h>

namespace bpl::graphics::draw::ops {
    class Text : public bpl::graphics::draw::ops::Op{
    public:
        Text();
        ~Text() override=default;

        bool Load(bpl::graphics::RendererPtr& renderer, const rapidjson::Value& value) override;
        bool Render(bpl::graphics::RendererPtr& renderer) override;

        void setValue(std::string value) { m_value = value;}
        void setColor(int red, int green, int blue);

        void setRegion(int x, int y, int w, int h);
        const SDL_Rect& getRegion() const { return m_textRect; }

        bool setHorizontalAlignment(const std::string& alignment);
        bool setVerticalAlignment(const std::string& alignment);
        void setFontName(const std::string& fontName);
        void setFontSize(int fontSize);

    private:
        std::string         m_value;
        std::string         m_fontName;
        graphics::Font::Alignment         m_vAlignment=graphics::Font::Alignment::Center;
        graphics::Font::Alignment         m_hAlignment=graphics::Font::Alignment::Center;
        int                 m_fontSize;
        SDL_Color           m_textColor = {0,0,0,0};
        SDL_Rect            m_textRect = {0,0,0,0};
        graphics::FontPtr   m_font;
    }; // class Text
    typedef std::shared_ptr<Text> TextPtr;
    typedef std::map<std::string, TextPtr> TextMap;

} // bpl::graphics::draw::ops

#endif //BPL_GRAPHICS_DRAW_OPS_FONT_H