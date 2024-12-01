//
// Created by Bradley Remedios on 10/25/24.
//
#include <iostream>

#include <bpl/graphics/FontCache.h>

#include "Debug.h"

namespace bpl::graphics {

    FontCachePtr FontCache::getInstance() {
        static FontCachePtr fontCache = std::make_shared<FontCache>();

        return fontCache;
    } // getInstance

    FontCache::~FontCache() {
        Clear();
    }

    void FontCache::Clear() {
        std::lock_guard<std::mutex>     lock(m_mutex);
        m_fonts.clear();
    }

    FontPtr FontCache::getFont(const std::string &name, int size) {
        std::string fontKey = name + std::to_string(size);

        std::lock_guard<std::mutex>     lock(m_mutex);

        //  return the font if we have it.
        if (m_fonts.contains(fontKey)) {
            return m_fonts[fontKey];
        }

        auto font = std::make_shared<bpl::graphics::Font>(name, size);

        if (!font->Load()) {
            ERROR_MSG("Font::Load() failed for : " << name << " " << size << "pt");

            return font;
        }

        m_fonts.emplace(fontKey, font);

        return font;
    } // getFont
} // bpl::graphics