//
// Created by Bradley Remedios on 11/14/24.
//

#ifndef BPL_GRAPHICS_DRAW_OPS_SPRITE_H
#define BPL_GRAPHICS_DRAW_OPS_SPRITE_H

#include <bpl/graphics/Sprite.h>

#include <bpl/graphics/draw/ops/Op.h>

namespace bpl::graphics::draw::ops {
    class Sprite : public bpl::graphics::draw::ops::Op{
    public:
        Sprite();
        ~Sprite() override;

        bool Load(bpl::graphics::RendererPtr& renderer, const rapidjson::Value& value) override;
        bool Render(bpl::graphics::RendererPtr& renderer) override;

        void SetSpriteName(const std::string& spriteName);
        void SetName(const std::string& name);
        void SetHeight(int height);
        void SetPosition(int x, int y);
        void SetFlipHorizontal(bool flip);
        void SetFlipVertical(bool flip);
        void SetSprite(bpl::graphics::SpritePtr& sprite);

    private:
        std::string                  m_name;
        std::string                  m_spriteName;
        int                          m_height=128;
        int                          m_x=0;
        int                          m_y=0;
        bool                         m_flipHorizontal=false;
        bool                         m_flipVertical=false;

        bpl::graphics::SpritePtr     m_sprite;
    }; // Sprite
} // bpl::graphics::draw::ops

#endif //BPL_GRAPHICS_DRAW_OPS_SPRITE_H