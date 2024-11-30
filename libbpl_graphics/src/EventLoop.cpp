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

    void EventLoop::addRenderObject(bpl::graphics::RenderObjectPtr renderObject) {
        std::lock_guard<std::mutex> lock(m_mutex);
        m_renderObjects.emplace_back(renderObject);
    } // addRenderObject

    void EventLoop::addRenderStartObject(bpl::graphics::RenderObjectPtr renderObject) {
        std::lock_guard<std::mutex> lock(m_mutex);
        m_renderStartObjects.emplace_back(renderObject);
    } // addRenderStartObject

    void EventLoop::addRenderEndObject(bpl::graphics::RenderObjectPtr renderObject) {
        std::lock_guard<std::mutex> lock(m_mutex);
        m_renderEndObjects.emplace_back(renderObject);
    } // addRenderEndObject

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

        // Perform rendering operations
        {
            std::lock_guard<std::mutex> lock(m_mutex);

            for (auto it : m_renderStartObjects) {
                it->RenderStart(m_renderer);
            }

            for (auto it : m_renderObjects) {
                it->Render(m_renderer);
            }

            for (auto it : m_renderEndObjects) {
                it->RenderEnd(m_renderer);
            }
        }

        DEBUG_MSG("Ending event loop ...");
    } // Run
}; // namespace bpl::graphics