//
// Created by Bradley Remedios on 12/05/24.
//

#ifndef BPL_GRAPHICS_UPDATEOBJECT_H
#define BPL_GRAPHICS_UPDATEOBJECT_H

#include <memory>

namespace bpl::graphics {
    class UpdateObject {
    public:
      UpdateObject()=default;
      virtual ~UpdateObject() =default;

      virtual void Destroy() {}
      virtual void WaitForTermination() {}

      virtual void Update(void) {};
    }; // UpdateObject

    typedef std::shared_ptr<UpdateObject> UpdateObjectPtr;
}; // bpl::graphics

#endif //BPL_GRAPHICS_UPDATEOBJECT_H