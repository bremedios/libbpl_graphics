//
// Created by Bradley Remedios on 11/29/24.
//

#ifndef BPL_GRAPHICS_LOGICOBJECT_H
#define BPL_GRAPHICS_LOGICOBJECT_H

#include <memory>

namespace bpl::graphics {
    class LogicObject {
    public:
      LogicObject()=default;
      virtual ~LogicObject() =default;

      virtual void Destroy() {}
      virtual void WaitForTermination() {}

      virtual void Logic(bpl::graphics::RendererPtr& renderer) {};
    }; // LogicObject

    typedef std::shared_ptr<LogicObject> LogicObjectPtr;
}; // bpl::graphics

#endif //BPL_GRAPHICS_LOGICOBJECT_H