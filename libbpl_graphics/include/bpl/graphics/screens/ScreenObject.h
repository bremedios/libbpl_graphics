//
// Created by Bradley Remedios on 12/5/24.
//

#ifndef BPL_GRAPHICS_SCREENOBJECT_H
#define BPL_GRAPHICS_SCREENOBJECT_H

#include <list>

#include <bpl/graphics/RenderObject.h>
#include <bpl/graphics/LogicObject.h>

namespace bpl::graphics::screens {
    class ScreenObject{
    public:
        ScreenObject() = default;
        virtual ~ScreenObject() = default;

        const std::string& getName() const {return m_name;}

        virtual const std::list<bpl::graphics::RenderObjectPtr>& getRenderObjects() { return m_renderObjects; }
        virtual const std::list<bpl::graphics::RenderObjectPtr>& getRenderStartObjects() { return m_renderStartObjects; }
        virtual const std::list<bpl::graphics::RenderObjectPtr>& getRenderEndObjects() { return m_renderEndObjects; }
        virtual const std::list<bpl::graphics::LogicObjectPtr>& getLogicObjects() { return m_logicObjects; }
    protected:
        std::list<bpl::graphics::RenderObjectPtr>   m_renderObjects;
        std::list<bpl::graphics::LogicObjectPtr>    m_logicObjects;
        std::list<bpl::graphics::RenderObjectPtr>   m_renderStartObjects;
        std::list<bpl::graphics::RenderObjectPtr>    m_renderEndObjects;
        std::string                                 m_name;
    }; // ScreenObject

    typedef std::shared_ptr<ScreenObject> ScreenObjectPtr;
}; // bpl::graphics::screens

#endif //BPL_GRAPHICS_SCREENOBJECT_H