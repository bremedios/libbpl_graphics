//
// Created by Bradley Remedios on 12/13/24.
//
#include <iostream>
#include <bpl/graphics/screens/ScreenObject.h>
#include <bpl/sys/Stopwatch.h>

namespace bpl::graphics::screens {
    void ScreenObject::Destroy() {
        m_renderObjects.clear();

        for (auto & obj: m_logicObjects) {
            obj->Destroy();
        }
        m_logicObjects.clear();

        m_renderEndObjects.clear();
    }
} // bpl::graphics::screens