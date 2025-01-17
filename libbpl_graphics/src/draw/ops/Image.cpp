//
// Created by Bradley Remedios on 11/21/24.
//

#include <bpl/sys/Path.h>
#include <bpl/storage/Json.h>

#include <bpl/graphics/Image.h>
#include <bpl/graphics/ImageCache.h>

#include <bpl/graphics/draw/ops/Image.h>

#include "../../Debug.h"

namespace bpl::graphics::draw::ops {
    Image::Image(const std::string& progName)
        : m_progName(progName) {
    }

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

        m_filename = bpl::sys::Path::getResourceFilename(m_filename, m_progName);

        // Optional
        storage::Json::Load(value, "dest", m_destination);

        if (!Reload(renderer)) {
            ERROR_MSG("Reload() failed");

            return false;
        }

        return true;
    } // Load

    bool Image::Reload(bpl::graphics::RendererPtr& renderer) {
        m_image = graphics::ImageCache::getInstance()->getImage(renderer, m_filename);

        if (!m_image->isValid()) {
            ERROR_MSG("Image not valid");

            return false;
        }

        return true;
    } // Reload

    bool Image::Render(graphics::RendererPtr& renderer) {
        return m_image->Draw(renderer, m_destination, m_flip);
    } // Render

} // bpl::graphics::draw::ops