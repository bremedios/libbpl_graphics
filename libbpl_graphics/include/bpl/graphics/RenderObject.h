//
// Created by Bradley Remedios on 11/29/24.
//

#ifndef BPL_GRAPHICS_RENDEROBJECT_H
#define BPL_GRAPHICS_RENDEROBJECT_H

#include <bpl/graphics/Renderer.h>

namespace bpl::graphics {
    class RenderObject {
    public:
        RenderObject()=default;
        virtual ~RenderObject() =default;

        virtual void RenderStart(bpl::graphics::RendererPtr renderer) {};
        virtual void Render(bpl::graphics::RendererPtr renderer) {};
        virtual void RenderEnd(bpl::graphics::RendererPtr renderer) {}
    }; // RenderObject

    typedef std::shared_ptr<RenderObject> RenderObjectPtr;
}; // bpl::graphics

#endif //BPL_GRAPHICS_RENDEROBJECT_H