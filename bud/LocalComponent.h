//
// Created by kier on 11/24/15.
//

#ifndef BUD_LOCALCOMPONENT_H
#define BUD_LOCALCOMPONENT_H

#include "Component.h"

namespace bud {

    class LocalComponent : public Component {
    public:
        using KeyboardEventHandler = std::function<void(const KeyboardEvent &)>;
        using MouseEventHandler = std::function<void(const MouseEvent &)>;
        using WindowEventHandler = std::function<void(const WindowEvent &)>;
        using QuitEventHandler = std::function<void()>;

        void whenKeyDown(const KeyboardEventHandler &handler);

        void whenKeyUp(const KeyboardEventHandler &handler);

        void whenKeyRepeat(const KeyboardEventHandler &handler);

        void whenMouseMove(const MouseEventHandler &handler);

        void whenMouseButtonDown(const MouseEventHandler &handler);

        void whenMouseButtonUp(const MouseEventHandler &handler);

        void whenMouseButtonClick(const MouseEventHandler &handler);

        void whenMouseButtonDoubleClick(const MouseEventHandler &handler);

        void whenMouseWheelScroll(const MouseEventHandler &handler);

        void whenWindowMotion(const WindowEventHandler &handler);

        void whenQuit(const QuitEventHandler &handler);

        virtual void onKeyDown(const KeyboardEvent &event);

        virtual void onKeyUp(const KeyboardEvent &event);

        virtual void onKeyRepeat(const KeyboardEvent &event);

        virtual void onMouseMove(const MouseEvent &event);

        virtual void onMouseButtonDown(const MouseEvent &event);

        virtual void onMouseButtonUp(const MouseEvent &event);

        virtual void onMouseButtonClick(const MouseEvent &event);

        virtual void onMouseButtonDoubleClick(const MouseEvent &event);

        virtual void onMouseWheelScroll(const MouseEvent &event);

        virtual void onWindowMotion(const WindowEvent &event);

        virtual void onQuit();

    private:
        KeyboardEventHandler m_KeyDown_handler = nullptr;
        KeyboardEventHandler m_KeyUp_handler = nullptr;
        KeyboardEventHandler m_KeyRepeat_handler = nullptr;
        MouseEventHandler m_MouseMove_handler = nullptr;
        MouseEventHandler m_MouseButtonDown_handler = nullptr;
        MouseEventHandler m_MouseButtonUp_handler = nullptr;
        MouseEventHandler m_MouseButtonClick_handler = nullptr;
        MouseEventHandler m_MouseButtonDoubleClick_handler = nullptr;
        MouseEventHandler m_MouseWheelScroll_handler = nullptr;
        WindowEventHandler m_WindowMotion_handler = nullptr;
        QuitEventHandler m_Quit_handler = nullptr;


    };

}


#endif //BUD_LOCALCOMPONENT_H
