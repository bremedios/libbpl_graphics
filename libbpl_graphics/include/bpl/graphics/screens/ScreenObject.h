//
// Created by Bradley Remedios on 12/5/24.
//

#ifndef BPL_GRAPHICS_SCREENOBJECT_H
#define BPL_GRAPHICS_SCREENOBJECT_H

#include <list>

#include <bpl/graphics/RenderObject.h>
#include <bpl/graphics/LogicObject.h>

namespace bpl::graphics::screens {
    class ScreenObject{
    public:
        ScreenObject() = default;
        virtual ~ScreenObject() = default;

        virtual std::list<bpl::graphics::RenderObjectPtr> getRenderObjects() = 0;
        virtual std::list<bpl::graphics::LogicObjectPtr> getLogicObjects() = 0;
    }; // ScreenObject

    typedef std::shared_ptr<ScreenObject> ScreenObjectPtr;
}; // bpl::graphics::screens

#endif //BPL_GRAPHICS_SCREENOBJECT_H