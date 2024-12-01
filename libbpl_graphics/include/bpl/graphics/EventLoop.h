//
// Created by Bradley Remedios on 11/29/24.
//

#ifndef BPL_GRAPHICS_EVENTLOOP_H
#define BPL_GRAPHICS_EVENTLOOP_H

#include <chrono>
#include <list>

#include <bpl/sys/Tick.h>

#include <bpl/graphics/Renderer.h>
#include <bpl/graphics/RenderObject.h>

namespace bpl::graphics {
    class EventLoop {
    public:
        EventLoop();
        virtual ~EventLoop()=default;

        void addRenderObject(bpl::graphics::RenderObjectPtr renderObject);
        void addRenderStartObject(bpl::graphics::RenderObjectPtr renderObject);
        void addRenderEndObject(bpl::graphics::RenderObjectPtr renderObject);

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

        std::list<bpl::graphics::RenderObjectPtr> m_renderObjects;
        std::list<bpl::graphics::RenderObjectPtr> m_renderStartObjects;
        std::list<bpl::graphics::RenderObjectPtr> m_renderEndObjects;

        std::mutex m_mutex;
    }; //  EventLoop

    typedef std::shared_ptr<EventLoop> EventLoopPtr;
}; //  bpl::graphics

#endif //BPL_GRAPHICS_EVENTLOOP_H