//
// Created by Bradley Remedios on 11/14/24.
//

#include <iostream>
#include <fstream>
#include <filesystem>

#include <rapidjson/document.h>
#include <rapidjson/istreamwrapper.h>

#include <bpl/graphics/ui/Window.h>

namespace bpl::graphics::ui {
    Window::Window() {
    }

    Window::Window(const std::string& layoutFile)
        : m_layoutFile(layoutFile) {
    }

    Window::~Window() {
        Destroy();
    }

    bool Window::Load(graphics::RendererPtr renderer) {
        /*if (!m_jsonLoader.Load(m_layoutFile, m_width, m_height, renderer, framerate)) {
            std::cerr << "Window::Load: JsonLoader::Load(...) failed" << std::endl;

            return false;
        }
*/
        return true;
    } // Load

    bool Window::Destroy() {
        //m_jsonLoader.Destroy();

        return true;
    } // Destroy

    void Window::Render(graphics::RendererPtr renderer) {
/**
        for (auto op : m_jsonLoader.GetOpList()) {
            if (!op->Render(renderer)) {
                std::cerr << "Window::Render: Failed to Render an Op" << std::endl;
            }
        }
*/
    } // Render
/*
    op::JsonLoader& Window::GetJsonLoader() {
        return m_jsonLoader;
    } // GetJsonLoader*

 */
} // bpl::graphics::ui