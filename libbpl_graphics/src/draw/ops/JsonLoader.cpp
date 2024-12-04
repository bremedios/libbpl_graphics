//
// Created by bradr on 11/14/24.
//
#include <filesystem>
#include <iostream>
#include <fstream>

#include <rapidjson/document.h>
#include <rapidjson/istreamwrapper.h>

#include <bpl/storage/Json.h>

#include <bpl/graphics/Renderer.h>


#include <bpl/graphics/draw/ops/JsonLoader.h>
#include <bpl/graphics/draw/ops/Fill.h>
#include <bpl/graphics/draw/ops/Text.h>
#include <bpl/graphics/draw/ops/Sprite.h>
#include <bpl/graphics/draw/ops/Image.h>

#include "../../Debug.h"

namespace bpl::graphics::draw::ops {
    JsonLoader::JsonLoader(const std::string& progName)
        :m_progName(progName) {
    }

    bool JsonLoader::Destroy() {
        m_drawOps.clear();
        m_drawOpMap.clear();
        m_sprites.clear();

        return true;
    } // Destroy

    OpList &JsonLoader::GetOpList() {
        return m_drawOps;
    } // GetOpList

    OpMap &JsonLoader::GetOpMap() {
        return m_drawOpMap;
    } // GetOpMap

    graphics::SpriteMap &JsonLoader::GetSpriteMap() {
        return m_sprites;
    } // GetSpriteMap

    void JsonLoader::AddOp_(const std::string& name, bpl::graphics::draw::ops::OpPtr op) {
        DEBUG_MSG("Adding Op \"" << name << "\"")

        m_drawOps.push_back(op);
        m_drawOpMap.insert(std::pair<std::string,bpl::graphics::draw::ops::OpPtr>(name, op));
    } // AddOp_

    bool JsonLoader::LoadSprites_(bpl::graphics::RendererPtr renderer, int framerate, const rapidjson::Value& sprites) {
        if (!sprites.IsArray()) {
            ERROR_MSG("Invalid sprites array")

            return false;
        }

        DEBUG_MSG("Loading Sprites");

        // Load sprites into our map.
        for (rapidjson::Value::ConstValueIterator itr = sprites.Begin(); itr != sprites.End(); ++itr) {
            if (!itr->IsObject()) {
                ERROR_MSG("Invalid sprites object");
            }

            bpl::graphics::SpritePtr sprite = std::make_shared<bpl::graphics::Sprite>(renderer,framerate);

            if (!sprite->Load(itr->GetObject()["filename"].GetString())) {
                ERROR_MSG("Failed to load sprite: " << itr->GetObject()["filename"].GetString());

                return false;
            }

            m_sprites[itr->GetObject()["name"].GetString()] = sprite;
            DEBUG_MSG("    Name:    " << itr->GetObject()["name"].GetString())
            DEBUG_MSG("    Filename:" << itr->GetObject()["filename"].GetString());
        }

        return true;
    } // LoadSprites_

    bool JsonLoader::LoadOpFill_(bpl::graphics::RendererPtr& renderer, const rapidjson::Value& fill) {
        bpl::graphics::draw::ops::Fill*   op      = new bpl::graphics::draw::ops::Fill();
        bpl::graphics::draw::ops::OpPtr   opPtr   = bpl::graphics::draw::ops::OpPtr(op);

        if (!op->Load(renderer, fill)) {
            ERROR_MSG("Failed to load op (Fill)");

            return false;
        }

        AddOp_(opPtr->getName(), opPtr);

        return true;
    } // LoadOpFill_


    bool JsonLoader::LoadOpText_(graphics::RendererPtr renderer,const rapidjson::Value &layout) {
        bpl::graphics::draw::ops::Text* op    = new bpl::graphics::draw::ops::Text();
        bpl::graphics::draw::ops::OpPtr opPtr = bpl::graphics::draw::ops::OpPtr(op);

        if (!op->Load(renderer, layout)) {
            ERROR_MSG("Failed to load op (Text)");

            return false;
        }

        AddOp_(opPtr->getName(), opPtr);

        return true;
    } // LoadOpText_



    bool JsonLoader::LoadOpImage_(graphics::RendererPtr renderer, const rapidjson::Value &layout) {
        bpl::graphics::draw::ops::Image* op    = new bpl::graphics::draw::ops::Image(m_progName);
        bpl::graphics::draw::ops::OpPtr opPtr = bpl::graphics::draw::ops::OpPtr(op);

        if (!op->Load(renderer, layout)) {
            ERROR_MSG("Failed to load op (Image)");

            return false;
        }

        AddOp_(opPtr->getName(), opPtr);

        return true;
    } // LoadOpImage_

    bool JsonLoader::LoadOpSprite_(graphics::RendererPtr renderer, const rapidjson::Value &layout) {
        bpl::graphics::draw::ops::Sprite* op      = new bpl::graphics::draw::ops::Sprite();
        bpl::graphics::draw::ops::OpPtr   opPtr   = bpl::graphics::draw::ops::OpPtr(op);

        bool        bValue=true;
        std::pair<int,int>  pairValue;
        std::string name;
        std::string str;
        int         intValue;
        SDL_Rect    rect;

        if (!bpl::storage::Json::Load(layout, "name", name)) {
            ERROR_MSG("No name set for sprite op");

            return false;
        }

        op->SetName(name);

        if (bpl::storage::Json::Load(layout, "visible", bValue)) {
            opPtr->setVisible(bValue);
        }

        if (!bpl::storage::Json::Load(layout, "sprite", str)) {
            ERROR_MSG("No sprite set for sprite op");

            return false;
        }

        if (!m_sprites.contains(str)) {
            ERROR_MSG("sprite name not valid");
            ERROR_MSG("    \"" << str << "\" not in the following");

            return false;
        }

        op->SetSprite(m_sprites[str]);

        if (!bpl::storage::Json::Load(layout, "height", intValue)) {
            ERROR_MSG("no height set");

            return false;
        }

        op->SetHeight(intValue);

        //  Optional
        if (bpl::storage::Json::Load(layout, "flip-horizontal", bValue)) {
            op->SetFlipHorizontal(bValue);
        }

        //  Optional
        if (bpl::storage::Json::Load(layout, "flip-vertical", bValue)) {
            op->SetFlipVertical(bValue);
        }

        if (!bpl::storage::Json::Load(layout, "location", pairValue)) {
            ERROR_MSG("no location set");

            return false;
        }

        op->SetPosition(pairValue.first, pairValue.second);

        if (!opPtr->Load(renderer, layout)) {
            ERROR_MSG("Failed to load op::Text");

            return false;
        }

        AddOp_(name, opPtr);

        return true;
    } // LoadOpSprite

    bool JsonLoader::LoadLayout_(bpl::graphics::RendererPtr& renderer, const rapidjson::Value& layout) {
        DEBUG_MSG("Loading Layout");

        if (!layout.IsObject()) {
            ERROR_MSG("Invalid layout object");

            return false;
        }

        if (!layout.HasMember("ops")) {
            ERROR_MSG("Has no ops");

            return false;
        }

        if (!layout["ops"].IsArray()) {
            ERROR_MSG("Invalid ops array");

            return false;
        }

        DEBUG_MSG("    Number of ops: " << std::to_string(layout["ops"].Size()))

        for (rapidjson::Value::ConstValueIterator itr = layout["ops"].GetArray().Begin(); itr != layout["ops"].End(); ++itr) {
            std::string type;

            if (!itr->IsObject()) {
                ERROR_MSG("Invalid layout object for op");

                return false;
            }

            if (!storage::Json::Load(*itr, "type", type)) {
                ERROR_MSG("Cannot load type for op");

                return false;
            }

            DEBUG_MSG("    Operation Type: " << type);

            if ("fill" == type) {
                LoadOpFill_(renderer, *itr);
            }
            else if ("text" == type) {
                LoadOpText_(renderer, *itr);
            }
            else if ("sprite" == type) {
                LoadOpSprite_(renderer, *itr);
            }
            else if ("image" == type) {
                LoadOpImage_(renderer, *itr);
            }
            else {
                ERROR_MSG("Unhandled operation type: " << type);
                ERROR_MSG("TODO: This should cause a failure, being allowed during development");

                return true;
            }
        }

        return true;
    } // LoadLayout_

    bool JsonLoader::Load(
        const std::string layoutFile,
        int width,
        int height,
        graphics::RendererPtr renderer) {

        m_layoutFile = layoutFile;

        DEBUG_MSG("Loading layout \"" << m_layoutFile << "\"");

        if (!std::filesystem::exists(m_layoutFile)) {
            ERROR_MSG("Layout file " << m_layoutFile << " does not exist.");

            return false;
        }

        std::ifstream ifs(m_layoutFile);

        rapidjson::IStreamWrapper isw(ifs);

        rapidjson::Document doc;

        doc.ParseStream(isw);

        if (!doc.IsObject()) {
            ERROR_MSG("No Root Object in " << m_layoutFile);

            return false;
        }

        if (doc.HasMember("sprites")) {
            DEBUG_MSG("    Found sprites");

            ERROR_MSG("FIX: hardcoding frame rate to 30");

            if (!LoadSprites_(renderer, 30, doc["sprites"])) {
                ERROR_MSG("Window::Load: Failed to load sprites");

                return false;
            }
        }

        if (doc.HasMember("layout")) {
            DEBUG_MSG("    Found layout");
            if (!doc.IsObject()) {
                ERROR_MSG("layout is not an object");
                return false;
            }

            std::string screenResolution = std::to_string(width) + "x" + std::to_string(height);

            rapidjson::Value layout = doc["layout"].GetObject();

            if (!layout.HasMember(screenResolution.c_str())) {
                ERROR_MSG("No matching screen resolution (" << screenResolution << ")");

                return false;
            }

            if (!LoadLayout_(renderer, layout[screenResolution.c_str()].GetObject())) {
                ERROR_MSG("Failed to load layout for " << screenResolution);

                return false;
            }
        }

        return true;
    } // Load
} // bpl::graphics::draw::ops