//
// Created by kier on 15-11-17.
//

#ifndef BUD_EVENT_H
#define BUD_EVENT_H

#include <SDL2/SDL.h>
#include "Input.h"
#include "Util.h"

namespace bud {

    class Event {
    public:
        Event(unsigned int windowID);

        virtual ~Event() = default;

        unsigned int windowID;
    };

    enum class WINDOW_STATUS {
        NONE,
        SHOWN,
        HIDDEN,
        EXPOSED,
        MOVED,
        RESIZED,
        SIZE_CHANGED,
        MINIMIZED,
        MAXIMIZED,
        RESTORED,
        ENTER,
        LEAVE,
        FOCUS_GAINED,
        FOCUS_LOST,
        CLOSE
    };

    class WindowEvent : public Event {
    public:
        WindowEvent(unsigned int windowID, WINDOW_STATUS type);

        WINDOW_STATUS type;
        int width;
        int height;
    };

    class MouseEvent : public Event {
    public:
        MouseEvent(unsigned int windowID, int x, int y, int xrel, int yrel, MOUSE::BUTTON button, DIRECTION direction);

        int x;
        int y;
        int xrel;
        int yrel;
        MOUSE::BUTTON button;
        DIRECTION direction;
    };

    class KeyboardEvent : public Event {
    public:
        KeyboardEvent(unsigned int windowID, KEY::CODE key);

        KEY::CODE key;
    };

    class EventListener {
    public:
        virtual ~EventListener() = default;

        static void PumpEvent();

        static void PullEvent(EventListener *listener);

        // 负责把原始的事件转化为自己的事件
        static void Convert(EventListener *listener, const SDL_Event &sdl_event);

        // 处理事件
        virtual void handleKeyDown(const KeyboardEvent &event) = 0;

        virtual void handleKeyUp(const KeyboardEvent &event) = 0;

        virtual void handleKeyRepeat(const KeyboardEvent &event) = 0;

        virtual void handleMouseMove(const MouseEvent &event) = 0;

        virtual void handleMouseButtonDown(const MouseEvent &event) = 0;

        virtual void handleMouseButtonUp(const MouseEvent &event) = 0;

        virtual void handleMouseButtonClick(const MouseEvent &event) = 0;

        virtual void handleMouseButtonDoubleClick(const MouseEvent &event) = 0;

        virtual void handleMouseWheelScroll(const MouseEvent &event) = 0;

        virtual void handleWindowMotion(const WindowEvent &event) = 0;

        virtual void handleQuit() = 0;
    };
}


#endif //BUD_EVENT_H
