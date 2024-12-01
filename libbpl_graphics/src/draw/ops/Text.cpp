//
// Created by Bradley Remedios on 11/14/24.
//
#include <iostream>
#include <cstring>

#include <bpl/sys/String.h>
#include <bpl/storage/Json.h>

#include <bpl/graphics/FontCache.h>
#include <bpl/graphics/draw/ops/Text.h>

#include "../../Debug.h"

namespace bpl::graphics::draw::ops {
    Text::Text() {
        m_type = "text";
    }

    bool Text::Load(bpl::graphics::RendererPtr& renderer, const rapidjson::Value& value) {
        if (!bpl::graphics::draw::ops::Op::Load(renderer, value)) {
            ERROR_MSG("Op::Load() failed");

            return false;
        }

        if (!bpl::storage::Json::Load(value, "color", m_textColor) ) {
            ERROR_MSG("Failed to load text color for Text Op");

            return false;
        }

        if (!bpl::storage::Json::Load(value, "dest", m_textRect)) {
            ERROR_MSG("Failed to load dest for Text Op");

            return false;
        }

        if (!bpl::storage::Json::Load(value, "value", m_value)) {
            ERROR_MSG("No value set for text op");

            return false;
        }

        if (!bpl::storage::Json::Load(value, "font", m_fontName)) {
            ERROR_MSG("No value set for text op");

            return false;
        }

        //  Optional
        if (!bpl::storage::Json::Load(value, "font-size", m_fontSize)) {
        }

        m_font = bpl::graphics::FontCache::getInstance()->getFont(m_fontName, m_fontSize);

        if (!m_font->isValid()) {
            ERROR_MSG("FontCache::getFont("<< m_fontName << ", " << m_fontSize << ") failed");

            return false;

        }

        std::string str;

        //  Optional
        if (bpl::storage::Json::Load(value, "halign", str)) {
            if (!setHorizontalAlignment(str)) {
                ERROR_MSG("TextOp::setHorizontalAlignment failed");

                return false;
            }
        }

        if (bpl::storage::Json::Load(value, "valign", str)) {
            if (!setVerticalAlignment(str)) {
                ERROR_MSG("TextOp::setVerticalAlignment failed");

                return false;
            }
        }

        return true;
    } // Load

    bool Text::Render(graphics::RendererPtr& renderer) {
        if (!m_visible) {
            return true;
        }

        if (!m_font->Render(renderer, m_textColor, m_value, m_textRect, m_hAlignment, m_vAlignment))
        {
            ERROR_MSG("Font::Render() failed.");

            return false;
        }
/*
        if (0 > SDL_SetRenderDrawColor(renderer->GetSdlRenderer(), m_textColor.r, m_textColor.g, m_textColor.b, 0)) {
            std::cerr << "SDL_SetRenderDrawColor failed.  SDL_ERROR: " << SDL_GetError() << std::endl;
        }

        if (0 > SDL_RenderDrawRect(renderer->GetSdlRenderer(), &m_textRect)) {
            std::cerr << "SDL_RenderDrawRect failed.  SDL_ERROR:" << SDL_GetError() << std::endl;
        }
*/
        return true;
    } // Render

    bool Text::setVerticalAlignment(const std::string &alignment) {
        std::string align = bpl::sys::string::tolower(alignment);

        if (align == "center") {
            m_vAlignment = graphics::Font::Alignment::Center;
            return true;
        } else if (align == "top") {
            m_vAlignment = graphics::Font::Alignment::Top;
            return true;
        } else if (align == "bottom") {
            m_vAlignment = graphics::Font::Alignment::Bottom;
            return true;
        } else {
            std::cerr << "Unknown Vertical Alignment " << align << std::endl;
        }

        return false;
    } // setVerticalAlignment

    bool Text::setHorizontalAlignment(const std::string &alignment) {
        std::string align = bpl::sys::string::tolower(alignment);

        if (align == "center") {
            m_hAlignment = graphics::Font::Alignment::Center;
            return true;
        } else if (align == "left") {
            m_hAlignment = graphics::Font::Alignment::Left;
            return true;
        } else if (align == "right") {
            m_hAlignment = graphics::Font::Alignment::Right;
            return true;
        }

        std::cerr << "Unknown Horizontal Alignment " << align << std::endl;

        return false;
    } // setHorizontalAlignment

    void Text::setRegion(int x, int y, int w, int h) {
        m_textRect.x = x;
        m_textRect.y = y;
        m_textRect.w = w;
        m_textRect.h = h;
    } // setRegion

    void Text::setColor(int red, int green, int blue) {
        m_textColor.r = red;
        m_textColor.g = green;
        m_textColor.b = blue;
    } // setColor

    void Text::setFontName(const std::string& fontName) {
        m_fontName = fontName;

        ERROR_MSG("Not supported");
    } // setFontName

    void Text::setFontSize(int fontSize) {
        m_fontSize = fontSize;

        ERROR_MSG("Not supported");
    } // setFontSize
} // bpl::graphics::draw::ops