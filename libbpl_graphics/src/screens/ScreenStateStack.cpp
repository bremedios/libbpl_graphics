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

    void ScreenStateStack::Push(bpl::graphics::screens::ScreenObjectPtr& screenObject) {
        m_screenStack.emplace(screenObject);

        m_eventLoop->Clear();
        m_eventLoop->addRenderObjects(screenObject->getRenderObjects());
        m_eventLoop->addLogicObjects(screenObject->getLogicObjects());
    } // Push

    bpl::graphics::screens::ScreenObjectPtr ScreenStateStack::Pop() {
        ScreenObjectPtr screenObject = m_screenStack.top();
        m_screenStack.pop();

        m_eventLoop->Clear();

        if (m_screenStack.size() == 0) {
            DEBUG_MSG("Popped last object");

            return screenObject;
        }

        m_eventLoop->addRenderObjects(screenObject->getRenderObjects());
        return screenObject;
    } // Pop
}; // ScreenStateStack