//
// Created by Bradley Remedios on 12/5/24.
//

#ifndef BPL_GRAPHICS_SCREENS_SCREENSTATEMANAGER_H
#define BPL_GRAPHICS_SCREENS_SCREENSTATEMANAGER_H

#include <memory>
#include <bpl/graphics/EventLoop.h>
#include <bpl/graphics/LogicObject.h>
#include <bpl/graphics/RenderObject.h>
#include <bpl/graphics/screens/ScreenObject.h>

namespace bpl::graphics::screens {
    class ScreenStateManager :  public bpl::graphics::LogicObject, public bpl::graphics::RenderObject{
    public:
        ScreenStateManager()=default;
        virtual ~ScreenStateManager()=default;

        void setEventLoop(bpl::graphics::EventLoopPtr& eventLoop) { m_eventLoop = eventLoop; };
    protected:
        bpl::graphics::EventLoopPtr     m_eventLoop;
    }; // ScreenStateManager
}; // bpl::graphics::screens
#endif //BPL_GRAPHICS_SCREENS_SCREENSTATEMANAGER_H