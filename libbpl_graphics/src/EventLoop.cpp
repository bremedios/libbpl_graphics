//
// Created by Bradley Remedios on 11/29/24.
//
#include <SDL2/SDL.h>
#include <bpl/graphics/EventLoop.h>

#include "Debug.h"

namespace bpl::graphics {

    EventLoop::EventLoop()
    : m_tick(std::chrono::milliseconds(20)) {
    }

    void EventLoop::setFramerate(int framerate) {
        m_framerate = framerate;

        m_tick.setPeriod((framerate * 1000) / 60);
    } // setFramerate

    void EventLoop::Run() {
        DEBUG_MSG("Starting event loop ...");
        SDL_Event event;

        m_tick.Reset();

        while (!m_terminate) {
            while (SDL_PollEvent(&event)) {
                if (event.type == SDL_QUIT) {

                    DEBUG_MSG("Received SDL_QUIT ...");
                    Terminate();
                }
            }

            m_tick.Wait();
        }

        DEBUG_MSG("Ending event loop ...");
    } // Run
}; // namespace bpl::graphics