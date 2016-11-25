//
// Created by kier on 15-11-17.
//

#include "Component.h"

namespace bud {

    /**
     * 下面是处理事件的方法，容器应该调用下面的方法
     */

    void Component::handleKeyDown(const KeyboardEvent &event) {
        if (!isListened()) return;
        this->onKeyDown(event);
    }

    void Component::handleKeyUp(const KeyboardEvent &event) {
        if (!isListened()) return;
        this->onKeyUp(event);
    }

    void Component::handleKeyRepeat(const KeyboardEvent &event) {
        if (!isListened()) return;
        this->onKeyRepeat(event);
    }

    void Component::handleMouseMove(const MouseEvent &event) {
        if (!isListened()) return;
        this->onMouseMove(event);
    }

    void Component::handleMouseButtonDown(const MouseEvent &event) {
        if (!isListened()) return;
        this->onMouseButtonDown(event);
    }

    void Component::handleMouseButtonUp(const MouseEvent &event) {
        if (!isListened()) return;
        this->onMouseButtonUp(event);
    }

    void Component::handleMouseButtonClick(const MouseEvent &event) {
        if (!isListened()) return;
        this->onMouseButtonClick(event);
    }

    void Component::handleMouseButtonDoubleClick(const MouseEvent &event) {
        if (!isListened()) return;
        this->onMouseButtonDoubleClick(event);
    }

    void Component::handleMouseWheelScroll(const MouseEvent &event) {
        if (!isListened()) return;
        this->onMouseWheelScroll(event);
    }

    void Component::handleWindowMotion(const WindowEvent &event) {
        if (!isListened()) return;
        this->onWindowMotion(event);
    }

    void Component::handleQuit() {
        if (!isListened()) return;
        this->onQuit();
    }

    /**
     * 下面是通过子类继承的方式要实现的方法
     */

    void Component::onKeyDown(const KeyboardEvent &event) {

    }

    void Component::onKeyUp(const KeyboardEvent &event) {

    }

    void Component::onKeyRepeat(const KeyboardEvent &event) {

    }

    void Component::onMouseMove(const MouseEvent &event) {

    }

    void Component::onMouseButtonDown(const MouseEvent &event) {

    }

    void Component::onMouseButtonUp(const MouseEvent &event) {

    }

    void Component::onMouseButtonClick(const MouseEvent &event) {

    }

    void Component::onMouseButtonDoubleClick(const MouseEvent &event) {

    }

    void Component::onMouseWheelScroll(const MouseEvent &event) {

    }

    void Component::onWindowMotion(const WindowEvent &event) {

    }

    void Component::onQuit() {

    }

    bool Component::isListened() const {
        return m_listened;
    }

    void Component::listen(bool listened) {
        this->m_listened = listened;
    }
}