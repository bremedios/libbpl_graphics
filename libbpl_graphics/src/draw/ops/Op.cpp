//
// Created by Bradley Remedios on 11/14/24.
//
#include <iostream>

#include <bpl/storage/Json.h>

#include <bpl/graphics/draw/ops/Op.h>

#include "../../Debug.h"

namespace bpl::graphics::draw::ops {
    Op::Op() {
      m_type = "Op";
    }

    bool Op::Load(bpl::graphics::RendererPtr& renderer, const rapidjson::Value& value) {
        if (!bpl::storage::Json::Load(value, "name", m_name)) {
          ERROR_MSG("Failed to load fill op name");

          return false;
        }

        //  Optional, we don't care either way as we've defaulted the value.
        bpl::storage::Json::Load(value, "visible", m_visible);

        return true;
    } // Load
}; // bpl::graphics::draw::ops