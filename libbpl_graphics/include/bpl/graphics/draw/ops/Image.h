//
// Created by Bradley Remedios on 11/21/24.
//
#ifndef BPL_GRAPHICS_DRAW_OPS_IMAGE_H
#define BPL_GRAPHICS_DRAW_OPS_IMAGE_H

#include <string>

#include <rapidjson/document.h>
#include <SDL2/SDL.h>

#include <bpl/graphics/Renderer.h>
#include <bpl/graphics/Image.h>
#include <bpl/graphics/draw/ops/Op.h>

namespace bpl::graphics::draw::ops {

    class Image  : public bpl::graphics::draw::ops::Op{
    public:
        Image() = default;
        ~Image() override = default;

        bool Load(bpl::graphics::RendererPtr& renderer, const rapidjson::Value& value) override;
        bool Reload(bpl::graphics::RendererPtr& renderer);
        bool Render(bpl::graphics::RendererPtr& renderer) override;

        void setRenderer(bpl::graphics::RendererPtr renderer) { m_renderer = renderer; }
        void setFilename(const std::string& filename) { m_filename = filename; }
        const std::string& getFilename() const { return m_filename; }
        void setDestination(const SDL_Rect& destination) { m_destination = destination; }
        const SDL_Rect& getDestination() const { return m_destination; }
        void setFlip(SDL_RendererFlip flip) { m_flip = flip; }
        SDL_RendererFlip getFlip() const { return m_flip; }

    private:
        std::string                   m_filename;
        bpl::graphics::RendererPtr    m_renderer;

        SDL_Rect                      m_destination;
        bpl::graphics::ImagePtr       m_image;
        SDL_RendererFlip              m_flip=SDL_FLIP_NONE;

    }; // Class Image

    typedef std::shared_ptr<Image>          ImagePtr;
    typedef std::map<std::string, ImagePtr> ImageMap;
} // bpl::graphics::draw::ops

#endif //BPL_GRAPHICS_DRAW_OPS_IMAGE_H