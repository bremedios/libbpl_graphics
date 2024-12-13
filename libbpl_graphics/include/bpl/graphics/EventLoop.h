//
// Created by Bradley Remedios on 11/29/24.
//

#ifndef BPL_GRAPHICS_EVENTLOOP_H
#define BPL_GRAPHICS_EVENTLOOP_H

#include <chrono>
#include <list>

#include <bpl/sys/Tick.h>
#include <bpl/sys/Timer.h>

#include <bpl/graphics/Renderer.h>
#include <bpl/graphics/RenderObject.h>
#include <bpl/graphics/LogicObject.h>
#include <bpl/graphics/UpdateObject.h>

#include <bpl/controls/Input.h>

namespace bpl::graphics {
    class EventLoop {
    public:
        EventLoop();
        virtual ~EventLoop()=default;

        // Logic operations operate second and can change state
        void addLogicObjects(const std::list<bpl::graphics::LogicObjectPtr>& logicObjects);
        void addLogicObject(bpl::graphics::LogicObjectPtr& logicObject);

        // Render operations are the last to execute
        void addRenderObjects(const std::list<bpl::graphics::RenderObjectPtr>& renderObjects);
        void addRenderObject(bpl::graphics::RenderObjectPtr& renderObject);
        void addRenderStartObject(bpl::graphics::RenderObjectPtr& renderObject);
        void addRenderEndObject(bpl::graphics::RenderObjectPtr& renderObject);

        void Next(std::list<bpl::graphics::LogicObjectPtr>  logicObjects,
                std::list<bpl::graphics::RenderObjectPtr> renderObjects,
                std::list<bpl::graphics::RenderObjectPtr> renderStartObjects,
                std::list<bpl::graphics::RenderObjectPtr> renderEndObjects);
        void Clear();
        void Run();
        void Terminate() {m_terminate = true;}

        void setFramerate(int framerate);
        int getFramerate() {return m_framerate;}

        void setRenderer(bpl::graphics::RendererPtr renderer) { m_renderer = renderer; }
        bpl::graphics::RendererPtr getRenderer() {return m_renderer;}

    private:
        bpl::graphics::RendererPtr  m_renderer;
        bool                        m_terminate=false;
        int                         m_framerate=60;
        bpl::sys::Tick              m_tick;
        bool                        m_clearOnRenderStart=true;

        // current objects
        std::list<bpl::graphics::LogicObjectPtr>  m_logicObjects;
        std::list<bpl::graphics::RenderObjectPtr> m_renderObjects;
        std::list<bpl::graphics::RenderObjectPtr> m_renderStartObjects;
        std::list<bpl::graphics::RenderObjectPtr> m_renderEndObjects;

        // next objects
        std::list<bpl::graphics::LogicObjectPtr>  m_nextLogicObjects;
        std::list<bpl::graphics::RenderObjectPtr> m_nextRenderObjects;
        std::list<bpl::graphics::RenderObjectPtr> m_nextRenderStartObjects;
        std::list<bpl::graphics::RenderObjectPtr> m_nextRenderEndObjects;

        bpl::controls::InputPtr         m_input;

        bpl::sys::Timer         m_joystickScanTimer;
        bool    m_nextObjReady = false;

        std::mutex m_mutex;
    }; //  EventLoop

    typedef std::shared_ptr<EventLoop> EventLoopPtr;
}; //  bpl::graphics

#endif //BPL_GRAPHICS_EVENTLOOP_H