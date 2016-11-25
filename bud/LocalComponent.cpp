//
// Created by kier on 11/24/15.
//

#include "LocalComponent.h"

namespace bud {

    void LocalComponent::whenKeyDown(const KeyboardEventHandler &handler) {
        this->m_KeyDown_handler = handler;
    }

    void LocalComponent::whenKeyUp(const KeyboardEventHandler &handler) {
        this->m_KeyUp_handler = handler;
    }

    void LocalComponent::whenKeyRepeat(const KeyboardEventHandler &handler) {
        this->m_KeyRepeat_handler = handler;
    }

    void LocalComponent::whenMouseMove(const MouseEventHandler &handler) {
        this->m_MouseMove_handler = handler;
    }

    void LocalComponent::whenMouseButtonDown(const MouseEventHandler &handler) {
        this->m_MouseButtonDown_handler = handler;
    }

    void LocalComponent::whenMouseButtonUp(const MouseEventHandler &handler) {
        this->m_MouseButtonUp_handler = handler;
    }

    void LocalComponent::whenMouseButtonClick(const MouseEventHandler &handler) {
        this->m_MouseButtonClick_handler = handler;
    }

    void LocalComponent::whenMouseButtonDoubleClick(const MouseEventHandler &handler) {
        this->m_MouseButtonDoubleClick_handler = handler;
    }

    void LocalComponent::whenMouseWheelScroll(const MouseEventHandler &handler) {
        this->m_MouseWheelScroll_handler = handler;
    }

    void LocalComponent::whenWindowMotion(const WindowEventHandler &handler) {
        this->m_WindowMotion_handler = handler;
    }

    void LocalComponent::whenQuit(const QuitEventHandler &handler) {
        this->m_Quit_handler = handler;
    }

    void LocalComponent::onKeyDown(const KeyboardEvent &event) {
        if (this->m_KeyDown_handler) this->m_KeyDown_handler(event);
    }

    void LocalComponent::onKeyUp(const KeyboardEvent &event) {
        if (this->m_KeyUp_handler) this->m_KeyUp_handler(event);
    }

    void LocalComponent::onKeyRepeat(const KeyboardEvent &event) {
        if (this->m_KeyRepeat_handler) this->m_KeyRepeat_handler(event);
    }

    void LocalComponent::onMouseMove(const MouseEvent &event) {
        if (this->m_MouseMove_handler) this->m_MouseMove_handler(event);
    }

    void LocalComponent::onMouseButtonDown(const MouseEvent &event) {
        if (this->m_MouseButtonDown_handler) this->m_MouseButtonDown_handler(event);
    }

    void LocalComponent::onMouseButtonUp(const MouseEvent &event) {
        if (this->m_MouseButtonUp_handler) this->m_MouseButtonUp_handler(event);
    }

    void LocalComponent::onMouseButtonClick(const MouseEvent &event) {
        if (this->m_MouseButtonClick_handler) this->m_MouseButtonClick_handler(event);
    }

    void LocalComponent::onMouseButtonDoubleClick(const MouseEvent &event) {
        if (this->m_MouseButtonDoubleClick_handler) this->m_MouseButtonDoubleClick_handler(event);
    }

    void LocalComponent::onMouseWheelScroll(const MouseEvent &event) {
        if (this->m_MouseWheelScroll_handler) this->m_MouseWheelScroll_handler(event);
    }

    void LocalComponent::onWindowMotion(const WindowEvent &event) {
        if (this->m_WindowMotion_handler) this->m_WindowMotion_handler(event);
    }

    void LocalComponent::onQuit() {
        if (this->m_Quit_handler) this->m_Quit_handler();
    }
}
