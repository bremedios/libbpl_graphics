//
// Created by Bradley Remedios on 11/21/24.
//

#include <bpl/graphics/Image.h>
#include <bpl/graphics/Surface.h>
#include <bpl/graphics/Texture.h>

#include "Debug.h"

namespace bpl::graphics {

bool Image::Load(graphics::RendererPtr renderer, const std::string& filename) {
    SurfacePtr surface (new Surface);

    if (!surface->CreateFromImage(filename)) {
        ERROR_MSG("Failed to create surface from Image: " << filename);

        return false;
    }

    m_texture = std::make_shared<Texture>();

    //
    //  This will destroy the surface once it has been created.
    //
    if(!m_texture->Create(renderer, surface, true)) {
        ERROR_MSG("Failed to create texture");

        return false;
    }

    m_texture->GetRect(m_imageRect);

    return true;
} // Load

bool Image::Draw(graphics::RendererPtr renderer, const SDL_Rect& dest, SDL_RendererFlip flip) {
    if (nullptr == renderer) {
        ERROR_MSG("Renderer is null");

        return false;
    }

    if (0 > SDL_RenderCopyEx(renderer->getSdlRenderer(), m_texture->getSdlTexture(), &m_imageRect, &dest, 0, nullptr, flip)) {
        ERROR_MSG("SDL_RenderCopyEx() failed.  SDL_ERROR: " << SDL_GetError());

        return false;
    }

    return true;
} // Draw

} // bpl::graphics