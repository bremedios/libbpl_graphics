//
// Created by Bradley Remedios on 11/14/24.
//

#ifndef BPL_GRAPHICS_DRAW_OPS_FILL_H
#define BPL_GRAPHICS_DRAW_OPS_FILL_H

#include <rapidjson/document.h>
#include <SDL2/SDL.h>

#include <bpl/graphics/draw/ops/Op.h>

namespace bpl::graphics::draw::ops {
    class Fill : public bpl::graphics::draw::ops::Op{
    public:
        Fill();
        ~Fill() override = default;

        bool Load(const rapidjson::Value& value) override;
        bool Render(graphics::RendererPtr& renderer) override;

        void setColor(int red, int green, int blue);
        void setFullscreen(bool value);
        void setRegion(int x, int y, int width, int height);
	private:
        SDL_Color    m_bg              = {0, 0, 0, 0};
        SDL_Rect     m_destRect        = {0, 0, 0, 0};
        bool         m_isFullscreen    = true;
    }; // class Fill

    typedef std::shared_ptr<Fill> FillPtr;
}; // bpl::graphics::draw::ops

#endif //BPL_GRAPHICS_DRAW_OPS_FILL_H