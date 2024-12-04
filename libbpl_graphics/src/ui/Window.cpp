//
// Created by Bradley Remedios on 11/14/24.
//

#include <iostream>
#include <fstream>
#include <filesystem>

#include <rapidjson/document.h>
#include <rapidjson/istreamwrapper.h>

#include <bpl/graphics/ui/Window.h>

#include "../../../../libbpl_sys/libbpl_sys/include/bpl/sys/Path.h"
#include "../Debug.h"

namespace bpl::graphics::ui {
    Window::Window() {
    }

    Window::Window(const std::string& layoutFile, const std::string& progName)
        : m_layoutFile(layoutFile)
        , m_progName(progName)
        , m_jsonLoader(progName){
    }

    Window::~Window() {
        Destroy();
    }

    bool Window::Load(graphics::RendererPtr renderer) {
        auto resourceFile = bpl::sys::Path::getResourceFilename(m_layoutFile, m_progName);

        if (resourceFile.empty()) {
            std::cerr << "Failed to load resource file name: " << m_layoutFile << std::endl;

            return false;
        }

        if (!m_jsonLoader.Load(resourceFile, renderer->getWindow()->getWidth(), renderer->getWindow()->getHeight(), renderer)) {
            ERROR_MSG("JsonLoader::Load(" << resourceFile << ",...) failed" << std::endl);

            return false;
        }

        return true;
    } // Load

    bool Window::Destroy() {
        m_jsonLoader.Destroy();

        return true;
    } // Destroy

    void Window::Render(graphics::RendererPtr renderer) {
        for (auto op : m_jsonLoader.GetOpList()) {
            if (!op->Render(renderer)) {
                ERROR_MSG("Failed to Render Op: " << op->getName() << " (" << op->getType() << ")");
            }
        }
    } // Render
} // bpl::graphics::ui