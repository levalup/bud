//
// Created by kier on 15-11-17.
//

#ifndef BUD_COMPONENT_H
#define BUD_COMPONENT_H

#include "Event.h"

#include <functional>

namespace bud {

    class Component : public EventListener {
    public:
        virtual ~Component() = default;

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

        bool isListened() const;

        void listen(bool listened = true);

    private:
        bool m_listened = true;
    };

}


#endif //BUD_COMPONENT_H
