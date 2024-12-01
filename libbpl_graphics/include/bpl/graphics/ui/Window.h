//
// Created by Bradley Remedios on 11/14/24.
//

#ifndef BPL_GRAPHICS_UI_WINDOWH
#define BPL_GRAPHICS_UI_WINDOWH

#include <map>
#include <string>

#include <rapidjson/document.h>

#include <bpl/graphics/RenderObject.h>
#include <bpl/graphics/draw/ops/JsonLoader.h>

namespace bpl::graphics::ui {

    class Window : public bpl::graphics::RenderObject {
    public:
        Window(const std::string& layoutFileName);

        virtual ~Window();

        //
        //  Setup and Teardown routines
        //
        [[nodiscard]] bool Load(graphics::RendererPtr renderer);
        bool Destroy();


        // RenderObject methods
        virtual void Render(bpl::graphics::RendererPtr renderer) override;


        bpl::graphics::draw::ops::JsonLoader& getJsonLoader() { return m_jsonLoader; };

    protected:
        Window();

        //bool LoadSprites_(graphics::RendererPtr renderer, int framerate, const rapidjson::Value& sprites);
        //bool LoadLayout_(const rapidjson::Value& layout);

        /*
        void AddOp_(const std::string& name, op::OpPtr op);


        int m_width = 0;
        int m_height = 0;*/
        bpl::graphics::draw::ops::JsonLoader m_jsonLoader;

        std::string m_layoutFile;

    private:
    };

    typedef std::shared_ptr<Window> WindowPtr;
} // bpl::graphics::ui

#endif //BPL_GRAPHICS_UI_WINDOWH