//
// Created by kier on 15-11-17.
//

#include "ComponentContainer.h"

namespace bud {

    ComponentContainer::~ComponentContainer() {
        // there is no need to clear for now
        // this->clearComponent();
    }

    void ComponentContainer::addComponent(Component *component) {
        this->m_child_component_list.push_back(component);
    }

    void ComponentContainer::removeComponent(Component *component) {
        this->m_child_component_list.remove(component);
    }

    void ComponentContainer::clearComponent() {
        this->m_child_component_list.clear();
    }

    void ComponentContainer::handleKeyDown(const KeyboardEvent &event) {
        if (!isListened()) return;
        Component::handleKeyDown(event);
        for (Component *component : this->m_child_component_list)
            component->handleKeyDown(event);
    }

    void ComponentContainer::handleKeyUp(const KeyboardEvent &event) {
        if (!isListened()) return;
        Component::handleKeyUp(event);
        for (Component *component : this->m_child_component_list)
            component->handleKeyUp(event);
    }

    void ComponentContainer::handleKeyRepeat(const KeyboardEvent &event) {
        if (!isListened()) return;
        Component::handleKeyRepeat(event);
        for (Component *component : this->m_child_component_list)
            component->handleKeyRepeat(event);
    }

    void ComponentContainer::handleMouseMove(const MouseEvent &event) {
        if (!isListened()) return;
        Component::handleMouseMove(event);
        for (Component *component : this->m_child_component_list)
            component->handleMouseMove(event);
    }

    void ComponentContainer::handleMouseButtonDown(const MouseEvent &event) {
        if (!isListened()) return;
        Component::handleMouseButtonDown(event);
        for (Component *component : this->m_child_component_list)
            component->handleMouseButtonDown(event);
    }

    void ComponentContainer::handleMouseButtonUp(const MouseEvent &event) {
        if (!isListened()) return;
        Component::handleMouseButtonUp(event);
        for (Component *component : this->m_child_component_list)
            component->handleMouseButtonUp(event);
    }

    void ComponentContainer::handleMouseButtonClick(const MouseEvent &event) {
        if (!isListened()) return;
        Component::handleMouseButtonClick(event);
        for (Component *component : this->m_child_component_list)
            component->handleMouseButtonClick(event);
    }

    void ComponentContainer::handleMouseButtonDoubleClick(const MouseEvent &event) {
        if (!isListened()) return;
        Component::handleMouseButtonDoubleClick(event);
        for (Component *component : this->m_child_component_list)
            component->handleMouseButtonDoubleClick(event);
    }

    void ComponentContainer::handleMouseWheelScroll(const MouseEvent &event) {
        if (!isListened()) return;
        Component::handleMouseWheelScroll(event);
        for (Component *component : this->m_child_component_list)
            component->handleMouseWheelScroll(event);
    }

    void ComponentContainer::handleWindowMotion(const WindowEvent &event) {
        if (!isListened()) return;
        Component::handleWindowMotion(event);
        for (Component *component : this->m_child_component_list)
            component->handleWindowMotion(event);
    }

    void ComponentContainer::handleQuit() {
        if (!isListened()) return;
        Component::handleQuit();
        for (Component *component : this->m_child_component_list)
            component->handleQuit();
    }

    unsigned long ComponentContainer::countChildComponent() {
        return this->m_child_component_list.size();
    }
}