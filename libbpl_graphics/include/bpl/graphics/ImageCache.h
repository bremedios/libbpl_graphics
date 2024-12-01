//
// Created by Bradley Remedios on 11/21/24.
//

#ifndef BPL_GRAPHICS_IMAGECACHE_H
#define BPL_GRAPHICS_IMAGECACHE_H

#include <string>
#include <map>
#include <list>

#include <bpl/graphics/Image.h>

namespace bpl::graphics {
    class ImageCache {
    public:
        static ImageCache* getInstance();

        ~ImageCache()=default;

        //  Use these to pre-load images into the cache.
        bool LoadImage(bpl::graphics::RendererPtr renderer, const std::string& filename);
        bool LoadImages(bpl::graphics::RendererPtr renderer, const std::list<std::string>& filenames);

        ImagePtr getImage(bpl::graphics::RendererPtr renderer, const std::string& filename);
        void Clear();
    private:
        ImageCache()=default;

        std::map<std::string, ImagePtr> m_cache;
    };

} // bpl::graphics

#endif //BPL_GRAPHICS_IMAGECACHE_H