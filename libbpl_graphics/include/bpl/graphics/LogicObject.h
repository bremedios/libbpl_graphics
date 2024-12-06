//
// Created by Bradley Remedios on 11/29/24.
//

#ifndef BPL_GRAPHICS_LOGICOBJECT_H
#define BPL_GRAPHICS_LOGICOBJECT_H

#include <memory>
#include <bpl/graphics/Renderer.h>
#include <bpl/controls/Input.h>

namespace bpl::graphics {
    class LogicObject {
    public:
      LogicObject()=default;
      virtual ~LogicObject() =default;

      virtual void Destroy() {}
      virtual void WaitForTermination() {}

      virtual void Logic(bpl::graphics::RendererPtr& renderer, bpl::controls::InputPtr& input) {};
    }; // LogicObject

    typedef std::shared_ptr<LogicObject> LogicObjectPtr;
}; // bpl::graphics

#endif //BPL_GRAPHICS_LOGICOBJECT_H