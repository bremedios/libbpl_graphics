//
// Created by Bradley Remedios on 10/25/24.
//

#ifndef BPL_GRAPHICS_SURFACE_H
#define BPL_GRAPHICS_SURFACE_H

#include <memory>
#include <SDL2/SDL.h>

#include <bpl/graphics/Window.h>

namespace bpl::graphics {

class Surface {
    public:
        Surface();
        Surface(SDL_Surface* surface);
        virtual ~Surface();


        [[nodiscard]] bool CreateFromImage(const std::string& filename);
        [[nodiscard]] bool Create(WindowPtr window);
        [[nodiscard]] bool Create(SDL_Surface* surface);
        bool Destroy();

        SDL_Surface* getSdlSurface() {return m_surface;}

    private:
        Surface(const Surface&);
        Surface& operator=(const Surface&);

        SDL_Surface* m_surface = nullptr;
};

    typedef std::shared_ptr<Surface> SurfacePtr;
} // bpl::graphics

#endif //BPL_GRAPHICS_SURFACE_H