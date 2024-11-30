//
// Created by Bradley Remedios on 11/29/24.
//

#ifndef BPL_GRAPHICS_EVENTLOOP_H
#define BPL_GRAPHICS_EVENTLOOP_H

#include <chrono>
#include <bpl/sys/Tick.h>

namespace bpl::graphics {
    class EventLoop {
    public:
        EventLoop();
        virtual ~EventLoop()=default;

        void Run();
        void Terminate() {m_terminate = true;}

        void setFramerate(int framerate);
        int getFramerate() {return m_framerate;}

    private:
        bool               m_terminate=false;
        int                m_framerate=60;
        bpl::sys::Tick     m_tick;
    }; //  EventLoop

    typedef std::shared_ptr<EventLoop> EventLoopPtr;
}; //  bpl::graphics

#endif //BPL_GRAPHICS_EVENTLOOP_H