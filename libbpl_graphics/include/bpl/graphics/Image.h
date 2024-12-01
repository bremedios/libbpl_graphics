//
// Created by Bradley Remedios on 11/21/24.
//

#ifndef BPL_GRAPHICS_IMAGE_H
#define BPL_GRAPHICS_IMAGE_H

#include <string>

#include <SDL2/SDL.h>

#include <bpl/graphics/Renderer.h>
#include <bpl/graphics/Texture.h>

namespace bpl::graphics {

    class Image {
    public:
        Image()=default;
        ~Image()=default;

        bool isValid() const {return m_texture.get() != nullptr && m_texture->getSdlTexture() != nullptr;}
        bool Load(bpl::graphics::RendererPtr renderer, const std::string& filename);
        bool Draw(bpl::graphics::RendererPtr renderer, const SDL_Rect& dest, SDL_RendererFlip flip=SDL_FLIP_NONE);

        int getWidth() {return m_imageRect.w;}
        int getHeight() {return m_imageRect.h;}

    private:
        bpl::graphics::TexturePtr    m_texture;

        SDL_Rect m_imageRect;
    };

    typedef std::shared_ptr<Image> ImagePtr;

} // bpl::graphics

#endif //BPL_GRAPHICS_IMAGE_H