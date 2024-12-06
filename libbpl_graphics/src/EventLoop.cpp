//
// Created by Bradley Remedios on 11/29/24.
//
#include <SDL2/SDL.h>
#include <bpl/graphics/EventLoop.h>

#include "Debug.h"

namespace bpl::graphics {

    EventLoop::EventLoop()
    : m_tick(std::chrono::milliseconds(20))
    , m_joystickScanTimer(std::chrono::milliseconds(1000)){
        m_input = std::make_shared<bpl::controls::Input>();

        if (!m_input->Create()) {
            ERROR_MSG("Failed to create input");
        }

        m_input->ScanJoysticks();
    }

    void EventLoop::setFramerate(int framerate) {
        m_framerate = framerate;

        m_tick.setPeriod(1000 / framerate);
    } // setFramerate

    void EventLoop::Clear() {
        std::lock_guard<std::mutex> lock(m_mutex);
        m_logicObjects.clear();
        m_renderObjects.clear();
    } // Clear

    void EventLoop::addLogicObjects(const std::list<bpl::graphics::LogicObjectPtr>& logicObjects) {
        std::lock_guard<std::mutex> lock(m_mutex);

        for (auto & it : logicObjects) {
            m_logicObjects.emplace_back(it);
        }
    } // addLogicObjects

    void EventLoop::addLogicObject(bpl::graphics::LogicObjectPtr& logicObject) {
        std::lock_guard<std::mutex> lock(m_mutex);
        m_logicObjects.emplace_back(logicObject);
    } // addLogicObject

    void EventLoop::addRenderObjects(const std::list<bpl::graphics::RenderObjectPtr>& renderObjects) {
        std::lock_guard<std::mutex> lock(m_mutex);

        for (auto & it : renderObjects) {
            m_renderObjects.emplace_back(it);
        }
    } // addRenderObjects

    void EventLoop::addRenderObject(bpl::graphics::RenderObjectPtr& renderObject) {
        std::lock_guard<std::mutex> lock(m_mutex);
        m_renderObjects.emplace_back(renderObject);
    } // addRenderObject

    void EventLoop::addRenderStartObject(bpl::graphics::RenderObjectPtr& renderObject) {
        std::lock_guard<std::mutex> lock(m_mutex);
        m_renderStartObjects.emplace_back(renderObject);
    } // addRenderStartObject

    void EventLoop::addRenderEndObject(bpl::graphics::RenderObjectPtr& renderObject) {
        std::lock_guard<std::mutex> lock(m_mutex);
        m_renderEndObjects.emplace_back(renderObject);
    } // addRenderEndObject

    void EventLoop::Next(std::list<bpl::graphics::LogicObjectPtr>  logicObjects,
        std::list<bpl::graphics::RenderObjectPtr> renderObjects,
        std::list<bpl::graphics::RenderObjectPtr> renderStartObjects,
        std::list<bpl::graphics::RenderObjectPtr> renderEndObjects) {
        m_nextLogicObjects = logicObjects;;
        m_nextRenderObjects = renderObjects;
        m_nextRenderStartObjects = renderStartObjects;
        m_nextRenderEndObjects = renderEndObjects;
        m_nextObjReady = true;
    } // Next

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

            //  We rescan our joysticks if our timer has expired.  This will
            //  allow us to pull in a joystick that is detected after the input
            //  is scanned
            if (m_joystickScanTimer.isExpired()) {
                m_input->ScanJoysticks();
                m_joystickScanTimer.Reset();
            }

            //  Run the input handler to pull any joysticks events that have
            //  occurred since last ran.
            m_input->Update();

            // Perform logic operations
            {
                std::lock_guard<std::mutex> lock(m_mutex);

                // WARN: We may want to do this differently.  If there are in
                // fact multiple objects this could be problematic if they are
                // accessing the Pressed routines as they clear on read.
                for (auto it : m_logicObjects) {
                    it->Logic(m_renderer, m_input);
                }
            }

            if (m_clearOnRenderStart) {
                m_renderer->RenderClear();
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

            m_renderer->RenderPresent();

            m_tick.Wait();

            if (m_nextObjReady) {
                m_logicObjects = m_nextLogicObjects;
                m_renderObjects = m_nextRenderObjects;
                m_renderStartObjects = m_nextRenderStartObjects;
                m_renderEndObjects = m_nextRenderEndObjects;

                m_nextLogicObjects.clear();
                m_nextRenderObjects.clear();
                m_nextRenderStartObjects.clear();
                m_nextRenderEndObjects.clear();
                m_nextObjReady = false;

                m_input->ClearPressedKeys();
            }
        }

        DEBUG_MSG("Ending event loop ...");
    } // Run
}; // namespace bpl::graphics