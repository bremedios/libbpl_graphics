//
// Created by Bradley Remedios on 10/25/24.
//

#ifndef BPL_GRAPHICS_TEXTURE_H
#define BPL_GRAPHICS_TEXTURE_H
#include <memory>

#include <bpl/graphics/Renderer.h>
#include <bpl/graphics/Surface.h>

namespace bpl::graphics {

    class Texture {
    public:
        Texture();
        ~Texture();

        void Destroy();

        [[nodiscard]] bool Create(RendererPtr renderer, SurfacePtr surface, bool destroySurface=false);
        SDL_Texture* getSdlTexture() { return m_texture; }
        void GetRect(SDL_Rect& rect);
    private:
        SDL_Texture* m_texture;
        int m_width;
        int m_height;

    };

    typedef std::shared_ptr<Texture> TexturePtr;

} // bpl::graphics

#endif //BPL_GRAPHICS_TEXTURE_H