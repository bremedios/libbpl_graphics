//
// Created by Bradley Remedios on 10/25/24.
//

#ifndef BPL_GRAPHICS_FONTCACHE_H
#define BPL_GRAPHICS_FONTCACHE_H
#include <map>
#include <memory>
#include <thread>

#include <bpl/graphics/Font.h>

namespace bpl::graphics {

    class FontCache {
    public:
        static std::shared_ptr<FontCache> getInstance();
        FontCache()=default;
        virtual ~FontCache();

        void Clear();
        FontPtr getFont(const std::string& name, int size);

    private:
        typedef std::map<std::string, FontPtr>     FontMap;
        FontMap                                    m_fonts;
        std::mutex                         m_mutex;
    }; // FontCache

    typedef std::shared_ptr<FontCache> FontCachePtr;
} // bpl::graphics

#endif //BPL_GRAPHICS_FONTCACHE_H