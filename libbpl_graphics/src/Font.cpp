//
// Created by Bradley Remedios on 10/25/24.
//
#include <iostream>

#include <bpl/graphics/Surface.h>
#include <bpl/graphics/Texture.h>
#include <bpl/graphics/Font.h>

#include "Debug.h"

namespace bpl::graphics {

    Font::Font(const std::string& name, int size)
        : m_fontName(name), m_fontSize(size){
    } // Font

    Font::~Font() {
        Release();
    }


    bool Font::Load() {
        m_font = TTF_OpenFont(m_fontName.c_str(), m_fontSize);

        if (nullptr == m_font) {
            ERROR_MSG("TTF_OpenFont(" << m_fontName << ", " << m_fontSize << ") failed.  SDL_Error: "<< SDL_GetError());

            return false;
        }

        return true;
    } // Load

    void Font::Release() {
        if (nullptr != m_font) {
            TTF_CloseFont(m_font);
            m_font = nullptr;
        }
    } // Release

    bool Font::Render(
        RendererPtr renderer,
        SDL_Color color,
        const std::string & text,
        const SDL_Rect& drawRegion,
        Alignment hAlignment,
        Alignment vAlignment) {

        if (nullptr == m_font) {
            ERROR_MSG("Font Invalid, Cannot render");

            return false;
        }

        //
        //  Create rendered surface with the desired text
        SDL_Surface* surf = TTF_RenderText_Blended(m_font, text.c_str(), color);

        if (nullptr == surf) {
            ERROR_MSG("TTF_RenderText_Blended() failed.  SDL_ERROR: " << SDL_GetError());

            return false;
        }

        graphics::SurfacePtr textSurface(new Surface(surf));

        TexturePtr texture(new Texture());

        //
        //  This will destroy the surface once it has been created.
        //
        if (!texture->Create(renderer, textSurface, true)) {
            ERROR_MSG("Texture Creation Failed");
        }

        SDL_Rect textureRect;

        texture->GetRect(textureRect);

        switch(hAlignment) {
            case Alignment::Center:
                //  If our text is bigger than the space, then we will cut off the left and right of the text.
                textureRect.x = drawRegion.x + (drawRegion.w - textureRect.w) / 2;
                break;
            case Alignment::Right:
                textureRect.x = (drawRegion.x + drawRegion.w) - textureRect.w;
            break;
            default:
            case Alignment::Left:
                textureRect.x = drawRegion.x;
            break;
        }

        switch (vAlignment) {
            case Alignment::Bottom:
                textureRect.y = (drawRegion.y + drawRegion.h) - textureRect.h;
                break;
            case Alignment::Top:
                textureRect.y = drawRegion.y;
                break;
            default:
            case Alignment::Center:
                textureRect.y = drawRegion.y + (drawRegion.h - textureRect.h) / 2;
                break;
        }

        if (0 > SDL_RenderCopy(renderer->getSdlRenderer(), texture->getSdlTexture(), nullptr, &textureRect)) {
            ERROR_MSG("SDL_RenderCopy() failed.  SDL_ERROR: " << SDL_GetError());
        }

        return true;
    } // Render
} // bpl::graphics