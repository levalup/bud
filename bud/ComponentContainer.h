//
// Created by kier on 15-11-17.
//

#ifndef BUD_COMPONENTCONTAINER_H
#define BUD_COMPONENTCONTAINER_H

#include "Component.h"

#include <list>

namespace bud {

    class ComponentContainer : public Component {
    public:
        virtual ~ComponentContainer();

        void addComponent(Component *component);

        void removeComponent(Component *component);

        void clearComponent();

        virtual void handleKeyDown(const KeyboardEvent &event) override;

        virtual void handleKeyUp(const KeyboardEvent &event) override;

        virtual void handleKeyRepeat(const KeyboardEvent &event) override;

        virtual void handleMouseMove(const MouseEvent &event) override;

        virtual void handleMouseButtonDown(const MouseEvent &event) override;

        virtual void handleMouseButtonUp(const MouseEvent &event) override;

        virtual void handleMouseButtonClick(const MouseEvent &event) override;

        virtual void handleMouseButtonDoubleClick(const MouseEvent &event) override;

        virtual void handleMouseWheelScroll(const MouseEvent &event) override;

        virtual void handleWindowMotion(const WindowEvent &event) override;

        virtual void handleQuit() override;

        unsigned long countChildComponent();

    private:
        std::list<Component *> m_child_component_list;

    };

}

#endif //BUD_COMPONENTCONTAINER_H
