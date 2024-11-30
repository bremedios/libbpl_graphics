//
// Created by Bradley Remedios on 10/25/24.
//
#include <iostream>

#include <bpl/graphics/FontCache.h>

#include "Debug.h"

namespace bpl::graphics {
    FontCache::~FontCache() {
        std::lock_guard<std::mutex>     lock(m_mutex);
        m_fonts.clear();
    }

    FontPtr FontCache::getFont(const std::string &name, int size) {
        std::string fontKey = name + std::to_string(size);

        std::lock_guard<std::mutex>     lock(m_mutex);

        FontMap::iterator it = m_fonts.find(fontKey);

        if (m_fonts.end() == it) {
            FontPtr font = std::make_shared<Font>(name, size);

            if (!font->isValid()) {
                ERROR_MSG("Failed to create font: " << fontKey);

                return nullptr;
            }

            m_fonts.insert(std::make_pair(fontKey, font));

            return font;
        }

        return it->second;
    } // getFont
} // bpl::graphics