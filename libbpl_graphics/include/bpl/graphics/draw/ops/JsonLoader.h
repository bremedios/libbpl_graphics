//
// Created by Bradley Remedios on 11/14/24.
//

#ifndef BPL_GRAPHICS_DRAW_OPS_JSONLOADER_H
#define BPL_GRAPHICS_DRAW_OPS_JSONLOADER_H

#include <string>
#include <map>

#include <bpl/graphics/Renderer.h>
#include <bpl/graphics/draw/ops/Op.h>
#include <bpl/graphics/draw/ops/Sprite.h>

namespace bpl::graphics::draw::ops {
      class JsonLoader {
      public:
          JsonLoader();
          ~JsonLoader();

          bool Load(const std::string layoutFile, int width, int height, graphics::RendererPtr renderer);
          bool Destroy();

          //  This is intentional.
          OpList& GetOpList();
          OpMap& GetOpMap();
          bpl::graphics::SpriteMap& GetSpriteMap();

      private:
          void AddOp_(const std::string& name, bpl::graphics::draw::ops::OpPtr op);

          bool LoadLayout_(bpl::graphics::RendererPtr& renderer, const rapidjson::Value& layout);
          bool LoadOpFill_(bpl::graphics::RendererPtr& renderer, const rapidjson::Value& layout);
          bool LoadOpImage_(graphics::RendererPtr renderer, const rapidjson::Value &layout);
          bool LoadOpText_(graphics::RendererPtr renderer, const rapidjson::Value &layout);
          bool LoadOpSprite_(graphics::RendererPtr renderer, const rapidjson::Value &layout);

          bool LoadSprites_(graphics::RendererPtr renderer, int framerate, const rapidjson::Value& sprites);


          std::string                     m_layoutFile;

          bpl::graphics::SpriteMap        m_sprites;
          OpList                          m_drawOps;
          OpMap                           m_drawOpMap;
      }; // JsonLoader
} //  bpl::graphics::draw::ops

#endif //BPL_GRAPHICS_DRAW_OPS_JSONLOADER_H