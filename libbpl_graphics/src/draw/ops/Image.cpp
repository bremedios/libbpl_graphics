//
// Created by Bradley Remedios on 11/21/24.
//
#include <bpl/storage/Json.h>

#include <bpl/graphics/Image.h>
#include <bpl/graphics/ImageCache.h>

#include <bpl/graphics/draw/ops/Image.h>

#include "../../Debug.h"

namespace bpl::graphics::draw::ops {
    bool Image::Load(bpl::graphics::RendererPtr& renderer, const rapidjson::Value& value) {
        SDL_Rect    rect;
        int         intValue;

        if (!bpl::graphics::draw::ops::Op::Load(renderer, value)) {
            ERROR_MSG("Op::Load() failed");

            return false;
        }

        if (!bpl::storage::Json::Load(value, "filename", m_filename)) {
            ERROR_MSG("No name set for sprite op");

            return false;
        }

        // Optional
        storage::Json::Load(value, "dest", m_destination);

        m_image = graphics::ImageCache::getInstance()->getImage(renderer, m_filename);

        if (!m_image->isValid()) {
            ERROR_MSG("Image not valid");

            return false;
        }
        return true;
    } // Load

    bool Image::Render(graphics::RendererPtr& renderer) {
        return m_image->Draw(renderer, m_destination, m_flip);
    } // Render

} // bpl::graphics::draw::ops