//
// Created by kier on 15-11-17.
//

#include "Event.h"

namespace bud {

    Event::Event(unsigned int windowID)
            : windowID(windowID) {
    }

    WindowEvent::WindowEvent(unsigned int windowID, WINDOW_STATUS type)
            : Event(windowID), type(type), width(-1), height(-1) {
    }

    MouseEvent::MouseEvent(unsigned int windowID, int x, int y, int xrel, int yrel, MOUSE::BUTTON button,
                           DIRECTION direction)
            : Event(windowID), x(x), y(y), xrel(xrel), yrel(yrel), button(button), direction(direction) {
    }

    KeyboardEvent::KeyboardEvent(unsigned int windowID, KEY::CODE key)
            : Event(windowID), key(key) {
    }

    void EventListener::PumpEvent() {
        SDL_PumpEvents();
    }

    void EventListener::PullEvent(EventListener *listener) {
        SDL_Event sdl_event;
        while (SDL_PollEvent(&sdl_event)) {
            EventListener::Convert(listener, sdl_event);
        }
    }

    void EventListener::Convert(EventListener *listener, const SDL_Event &sdl_event) {
        switch (sdl_event.type) {
            default:
                break;
            case SDL_QUIT:
                listener->handleQuit();
                break;
            case SDL_WINDOWEVENT: {
                WindowEvent window_event(sdl_event.window.windowID, WINDOW_STATUS::NONE);
                switch ((SDL_WindowEventID) sdl_event.window.event) {
                    default:
                        break;
                    case SDL_WINDOWEVENT_NONE:
                        window_event.type = WINDOW_STATUS::NONE;
                        break;
                    case SDL_WINDOWEVENT_SHOWN:
                        window_event.type = WINDOW_STATUS::SHOWN;
                        break;
                    case SDL_WINDOWEVENT_HIDDEN:
                        window_event.type = WINDOW_STATUS::HIDDEN;
                        break;
                    case SDL_WINDOWEVENT_EXPOSED:
                        window_event.type = WINDOW_STATUS::EXPOSED;
                        break;
                    case SDL_WINDOWEVENT_MOVED:
                        window_event.type = WINDOW_STATUS::MOVED;
                        break;
                    case SDL_WINDOWEVENT_RESIZED:
                        window_event.type = WINDOW_STATUS::RESIZED;
                        break;
                    case SDL_WINDOWEVENT_SIZE_CHANGED:
                        window_event.type = WINDOW_STATUS::SIZE_CHANGED;
                        window_event.width = sdl_event.window.data1;
                        window_event.height = sdl_event.window.data2;
                        break;
                    case SDL_WINDOWEVENT_MINIMIZED:
                        window_event.type = WINDOW_STATUS::MINIMIZED;
                        break;
                    case SDL_WINDOWEVENT_MAXIMIZED:
                        window_event.type = WINDOW_STATUS::MAXIMIZED;
                        break;
                    case SDL_WINDOWEVENT_RESTORED:
                        window_event.type = WINDOW_STATUS::RESTORED;
                        break;
                    case SDL_WINDOWEVENT_ENTER:
                        window_event.type = WINDOW_STATUS::ENTER;
                        break;
                    case SDL_WINDOWEVENT_LEAVE:
                        window_event.type = WINDOW_STATUS::LEAVE;
                        break;
                    case SDL_WINDOWEVENT_FOCUS_GAINED:
                        window_event.type = WINDOW_STATUS::FOCUS_GAINED;
                        break;
                    case SDL_WINDOWEVENT_FOCUS_LOST:
                        window_event.type = WINDOW_STATUS::FOCUS_LOST;
                        break;
                    case SDL_WINDOWEVENT_CLOSE:
                        window_event.type = WINDOW_STATUS::CLOSE;
                        break;
                }
                listener->handleWindowMotion(window_event);
            }
                break;
            case SDL_KEYDOWN:
                if (sdl_event.key.repeat)
                    listener->handleKeyRepeat(
                            KeyboardEvent(sdl_event.key.windowID, (KEY::CODE) sdl_event.key.keysym.scancode));
                else
                    listener->handleKeyDown(
                            KeyboardEvent(sdl_event.key.windowID, (KEY::CODE) sdl_event.key.keysym.scancode));
                break;
            case SDL_KEYUP:
                listener->handleKeyUp(
                        KeyboardEvent(sdl_event.key.windowID, (KEY::CODE) sdl_event.key.keysym.scancode));
                break;
            case SDL_MOUSEMOTION:
                listener->handleMouseMove(
                        MouseEvent(sdl_event.motion.windowID,
                                   sdl_event.motion.x, sdl_event.motion.y, sdl_event.motion.xrel,
                                   sdl_event.motion.yrel, MOUSE::NONE, DIRECTION::NONE));
                break;
            case SDL_MOUSEBUTTONDOWN: {
                MouseEvent mouse_event(sdl_event.motion.windowID,
                                       sdl_event.button.x, sdl_event.button.y, 0, 0,
                                       MOUSE::NONE, DIRECTION::NONE);
                switch (sdl_event.button.button) {
                    default:
                        break;
                    case SDL_BUTTON_LEFT:
                        mouse_event.button = MOUSE::LEFT;
                        break;
                    case SDL_BUTTON_MIDDLE:
                        mouse_event.button = MOUSE::MIDDLE;
                        break;
                    case SDL_BUTTON_RIGHT:
                        mouse_event.button = MOUSE::RIGHT;
                        break;
                    case SDL_BUTTON_X1:
                        mouse_event.button = MOUSE::X1;
                        break;
                    case SDL_BUTTON_X2:
                        mouse_event.button = MOUSE::X2;
                        break;
                }
                listener->handleMouseButtonDown(mouse_event);
            }
                break;
            case SDL_MOUSEBUTTONUP: {
                MouseEvent mouse_event(sdl_event.button.windowID,
                                       sdl_event.button.x, sdl_event.button.y, 0, 0,
                                       MOUSE::NONE, DIRECTION::NONE);
                switch (sdl_event.button.button) {
                    default:
                        break;
                    case SDL_BUTTON_LEFT:
                        mouse_event.button = MOUSE::LEFT;
                        break;
                    case SDL_BUTTON_MIDDLE:
                        mouse_event.button = MOUSE::MIDDLE;
                        break;
                    case SDL_BUTTON_RIGHT:
                        mouse_event.button = MOUSE::RIGHT;
                        break;
                    case SDL_BUTTON_X1:
                        mouse_event.button = MOUSE::X1;
                        break;
                    case SDL_BUTTON_X2:
                        mouse_event.button = MOUSE::X2;
                        break;
                }
                listener->handleMouseButtonUp(mouse_event);
                switch (sdl_event.button.clicks) {
                    default:
                        break;
                    case 1:
                        listener->handleMouseButtonClick(mouse_event);
                        break;
                    case 2:
                        listener->handleMouseButtonDoubleClick(mouse_event);
                        break;
                }
            }
                break;
            case SDL_MOUSEWHEEL:
                listener->handleMouseWheelScroll(
                        MouseEvent(sdl_event.wheel.windowID,
                                   sdl_event.wheel.x, sdl_event.wheel.y, 0, 0,
                                   MOUSE::NONE, sdl_event.wheel.y > 0 ? DIRECTION::UP : DIRECTION::DOWN));
                break;
        }
    }
}