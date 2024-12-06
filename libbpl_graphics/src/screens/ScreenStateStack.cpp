//
// Created by Bradley Remedios on 12/5/24.
//
#include <memory>

#include <bpl/graphics/screens/ScreenStateStack.h>

#include "../Debug.h"

namespace bpl::graphics::screens {
    std::shared_ptr<ScreenStateStack> ScreenStateStack::getInstance() {
        static ScreenStateStackPtr ptr = std::make_shared<ScreenStateStack>();

        return ptr;
    } // getInstance

    void ScreenStateStack::AddScreen(bpl::graphics::screens::ScreenObjectPtr& screenObject) {
        m_screenObjects.emplace(screenObject->getName(), screenObject);
    } // AddScreen

    void ScreenStateStack::Push(const std::string& name) {
        // This is a reserved value to cause us to quit.
        if (name == "QUIT PROGRAM") {
            DEBUG_MSG("QUIT PROGRAM Received, terminating...");
            m_eventLoop->Terminate();
            return;
        }

        DEBUG_MSG("Screen '" << name << "' Pushed to stack");

        if (!m_screenObjects.contains(name)) {
            ERROR_MSG("Request to push screen that doesn't exist, ignoring");

            return;
        }

        auto screenObject = m_screenObjects[name];

        m_eventLoop->Next(
            screenObject->getLogicObjects(),
            screenObject->getRenderObjects(),
            screenObject->getRenderStartObjects(),
            screenObject->getRenderEndObjects());

        m_screenStack.push(name);
        DEBUG_MSG("Push Completed");
    } // Push

    void ScreenStateStack::Pop() {
        m_screenStack.pop();

        if (m_screenStack.size() == 0) {
            DEBUG_MSG("Popped last object");

            return;
        }

        auto screenObject = m_screenObjects[m_screenStack.top()];

        m_eventLoop->Next(
            screenObject->getLogicObjects(),
            screenObject->getRenderObjects(),
            screenObject->getRenderStartObjects(),
            screenObject->getRenderEndObjects());
    } // Pop
}; // ScreenStateStack