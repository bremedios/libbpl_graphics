//
// Created by Bradley Remedios on 11/14/24.
//

#include <bpl/graphics/draw/ops/Sprite.h>

#include "../../Debug.h"

namespace bpl::graphics::draw::ops {
    Sprite::Sprite() {
        m_type = "sprite";
    }

    Sprite::~Sprite() = default;

    bool Sprite::Load(bpl::graphics::RendererPtr& renderer, const rapidjson::Value& value) {
        m_sprite->setPosition(m_x, m_y);

        m_sprite->ScaleToHeight(m_height);

        if (m_flipHorizontal) {
            m_sprite->FlipHorizontal();
        }

        if (m_flipVertical) {
            m_sprite->FlipVertical();
        }

        return true;
    } // Load

    bool Sprite::Render(bpl::graphics::RendererPtr& renderer) {
        if (!m_visible) {
            return true;
        }

        m_sprite->Draw();

        return true;
    }

    void Sprite::SetSprite(bpl::graphics::SpritePtr& sprite) {
        m_sprite = sprite;
    } // SetSprite

    void Sprite::SetSpriteName(const std::string& spriteName) {
        m_spriteName = spriteName;
    } // SetSpriteName

    void Sprite::SetName(const std::string& name) {
        m_name = name;
    } // SetName

    void Sprite::SetHeight(int height) {
        m_height = height;
    } // SetHeight

    void Sprite::SetPosition(int x, int y) {
        m_x = x;
        m_y = y;
    } // SetPosition

    void Sprite::SetFlipHorizontal(bool flip) {
        m_flipHorizontal = flip;
    } // SetFlipHorizontal

    void Sprite::SetFlipVertical(bool flip) {
        m_flipVertical = flip;
    } // SetFlipVertical
} // bpl::graphics::draw::ops