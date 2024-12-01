//
// Created by Bradley Remedios on 11/14/24.
//

#ifndef BPL_GRAPHICS_DRAW_OPS_OP_H
#define BPL_GRAPHICS_DRAW_OPS_OP_H

#include <list>
#include <map>
#include <memory>

#include <rapidjson/document.h>

#include <bpl/graphics/Renderer.h>

namespace bpl::graphics::draw::ops {
        class Op {
        public:
            Op ();
            virtual ~Op() = default;

            virtual bool Load(bpl::graphics::RendererPtr& renderer, const rapidjson::Value& value);
            virtual bool Render(bpl::graphics::RendererPtr& renderer)=0;

            virtual const std::string& getType() { return m_type;}
            virtual const bool isVisible() { return m_visible;}
            virtual void setVisible(bool visible) { m_visible = visible; }
            virtual const std::string& getType() const { return m_type;}
            virtual const std::string& getName() const { return m_name;}
        protected:
            std::string m_name;
            std::string m_type;
            bool m_visible=true;
        }; // Op

        typedef std::shared_ptr<Op>                 OpPtr;
        typedef std::list<OpPtr>                    OpList;
        typedef std::map<std::string, OpPtr>        OpMap;
} // bpl::graphics::draw::ops


#endif //BPL_GRAPHICS_DRAW_OPS_OP_H