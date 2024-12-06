//
// Created by Bradley Remedios on 12/5/24.
//

#ifndef BPL_GRAPHICS_SCREENS_SCREENSTATESTACK_H
#define BPL_GRAPHICS_SCREENS_SCREENSTATESTACK_H
#include <memory>
#include <stack>
#include <map>

#include <bpl/graphics/screens/ScreenObject.h>
#include <bpl/graphics/screens/ScreenStateManager.h>

namespace bpl::graphics::screens {
    class ScreenStateStack : public bpl::graphics::screens::ScreenStateManager {
    public:
        static std::shared_ptr<ScreenStateStack> getInstance();

        ScreenStateStack() = default;

        ~ScreenStateStack() override = default;

        void AddScreen(bpl::graphics::screens::ScreenObjectPtr& screenObject);

        //
        //  These will allow us to push and pop screens into the screen.  This allows
        //  us to easily go forwards and backwards through the ui.
        //
        void Push(const std::string& name);
        void Pop();

    private:
        std::map<std::string,bpl::graphics::screens::ScreenObjectPtr> m_screenObjects;
        std::stack<std::string>      m_screenStack;
    }; // ScreenStateStack

    typedef std::shared_ptr<ScreenStateStack> ScreenStateStackPtr;

}; // bpl::graphics::screens
#endif //BPL_GRAPHICS_SCREENS_SCREENSTATESTACK_H