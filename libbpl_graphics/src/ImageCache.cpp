//
// Created by Bradley Remedios on 11/21/24.
//

#include <bpl/graphics/ImageCache.h>

#include "Debug.h"

namespace bpl::graphics {
    ImageCache* ImageCache::getInstance() {
        static ImageCache instance;

        return &instance;
    } // getInstance

    bool ImageCache::LoadImage(bpl::graphics::RendererPtr renderer, const std::string& filename) {
        if (m_cache.contains(filename)) {
            DEBUG_MSG("Image cache hit: " << filename);

            return true;
        }

        bpl::graphics::ImagePtr image = std::make_shared<Image>();

        if (!image->Load(renderer, filename)) {
            ERROR_MSG("Failed to load image: " << filename);

            return false;
        }

        m_cache.emplace(filename, image);

        return true;
    } // LoadImage

    bool ImageCache::LoadImages(bpl::graphics::RendererPtr renderer, const std::list<std::string>& filenames) {
        bool result = true;

        for (auto& it : filenames) {
            if (!LoadImage(renderer, it)) {
                ERROR_MSG("Failed to load image: " << it);
                result = false;
            }
        }

        return result;
    } // LoadImages

    bpl::graphics::ImagePtr ImageCache::getImage(bpl::graphics::RendererPtr renderer, const std::string& filename) {
        if (!LoadImage(renderer, filename)) {
            ERROR_MSG("Failed to load image: " << filename);

            return std::make_shared<bpl::graphics::Image>();
        }

        return m_cache[filename];
    } // getImage

    void ImageCache::Clear() {
        m_cache.clear();
    } // Clear

} // bpl::graphics