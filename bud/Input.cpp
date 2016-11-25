//
// Created by kier on 11/23/15.
//

#include <SDL2/SDL_stdinc.h>
#include <SDL2/SDL_keyboard.h>
#include "Input.h"
#include <limits>
#include <SDL2/SDL_events.h>
#include <iostream>

using namespace std;

namespace bud {

    // 记录输入操作的帧数，不对外开放
    unsigned int input_frame = 0;

    // 基本设置，保存的按键状态
    const unsigned int NUM_STORE = 10;

    // 键盘输入的操作码
    const unsigned int NUM_SCANCODES = (unsigned int) KEY::NUM_SCANCODES;
    Uint8 PreKeyState[NUM_SCANCODES];
    Uint8 KeyState[NUM_SCANCODES];
    unsigned int KeyTriggerFrame[NUM_SCANCODES][NUM_STORE];
    bool ToggleKeyState[NUM_SCANCODES];

    // 鼠标输入操作码
    Point<int> MousePosition;
    Point<int> PreMousePosition;
    Point<int> RelativeMousePosition;
    Uint32 MouseBitmask;
    const unsigned int NUM_MOUSE_BUTTON = (unsigned int) MOUSE::NUM_SCANCODES;
    int PreMouseState[NUM_MOUSE_BUTTON];
    int MouseState[NUM_MOUSE_BUTTON];
    unsigned int MouseTriggerFrame[NUM_MOUSE_BUTTON][NUM_STORE];
    bool ToggleMouseState[NUM_MOUSE_BUTTON];

    // 基本设置属性，
    int key_repeat_skip = 3;
    int key_repeat_rate = 6;
    int key_combo_space = 15;
    int key_click_space = 15;
    int mouse_repeat_skip = 0;
    int mouse_repeat_rate = 6;
    int mouse_combo_space = 15;
    int mouse_click_space = 15;

    void Input::init() {
        input_frame = 3600;
        // 初始化键盘
        memset(PreKeyState, 0, sizeof(Uint8) * NUM_SCANCODES);
        memset(KeyState, 0, sizeof(Uint8) * NUM_SCANCODES);
        memset(KeyTriggerFrame, 0, sizeof(unsigned int) * NUM_SCANCODES * NUM_STORE);
        for (size_t i = 0; i < NUM_SCANCODES; ++i) {
            ToggleKeyState[i] = false;
        }
        // 初始化鼠标
        MouseBitmask = SDL_GetMouseState(&MousePosition.x, &MousePosition.y);
        PreMousePosition = MousePosition;
        RelativeMousePosition.set(0, 0);
        memset(PreMouseState, 0, sizeof(int) * NUM_MOUSE_BUTTON);
        memset(MouseState, 0, sizeof(int) * NUM_MOUSE_BUTTON);
        memset(MouseTriggerFrame, 0, sizeof(unsigned int) * NUM_MOUSE_BUTTON * NUM_STORE);
        for (size_t i = 0; i < NUM_MOUSE_BUTTON; ++i) {
            ToggleMouseState[i] = false;
        }
    }

    void Input::update() {
        // SDL_PumpEvents();    // 保证事件被收集，这里由外部保证，
        input_frame++;  // 帧数放到前面更新，保证后面按键处理的是当前帧的情况
        // 处理键盘输入
        int key_num;
        const Uint8 *current_key_state = SDL_GetKeyboardState(&key_num);
        unsigned long current_key_num = (unsigned int) key_num < NUM_SCANCODES ? (unsigned int) key_num : NUM_SCANCODES;
        memcpy(PreKeyState, KeyState, sizeof(Uint8) * NUM_SCANCODES);
        memcpy(KeyState, current_key_state, sizeof(Uint8) * current_key_num);
        for (size_t i = 0; i < NUM_SCANCODES; ++i) {
            if (KeyState[i] && !PreKeyState[i]) {
                for (size_t s = NUM_STORE - 1; s > 0; --s) {
                    KeyTriggerFrame[i][s] = KeyTriggerFrame[i][s - 1];
                }
                KeyTriggerFrame[i][0] = input_frame;
                ToggleKeyState[i] = !ToggleKeyState[i];
            }
        }
        // 处理鼠标输入
        PreMousePosition = MousePosition;
        MouseBitmask = SDL_GetMouseState(&MousePosition.x, &MousePosition.y);
        RelativeMousePosition = MousePosition - PreMousePosition;
        for (size_t i = 0; i < NUM_MOUSE_BUTTON; ++i) {
            PreMouseState[i] = MouseState[i];
            MouseState[i] = MouseBitmask & SDL_BUTTON(i);
            if (MouseState[i] && !PreMouseState[i]) {
                for (size_t s = NUM_STORE - 1; s > 0; --s) {
                    MouseTriggerFrame[i][s] = MouseTriggerFrame[i][s - 1];
                }
                MouseTriggerFrame[i][0] = input_frame;
                ToggleMouseState[i] = !ToggleMouseState[i];
            }
        }
    }

    void Input::setKeyRepeatProperty(int skip, int rate) {
        key_repeat_skip = skip;
        key_repeat_rate = rate;
    }

    void Input::setKeyComboProperty(int space) {
        key_combo_space = space;
    }

    void Input::setKeyClickProperty(int space) {
        key_click_space = space;
    }

    void Input::getKeyRepeatProperty(int *skip, int *rate) {
        if (skip) *skip = key_repeat_skip;
        if (rate) *rate = key_repeat_rate;
    }

    void Input::getKeyComboProperty(int *space) {
        if (space) *space = key_combo_space;
    }

    void Input::getKeyClickProperty(int *space) {
        if (space) *space = key_click_space;
    }

    void Input::setMouseRepeatProperty(int skip, int rate) {
        mouse_repeat_skip = skip;
        mouse_repeat_rate = rate;
    }

    void Input::setMouseComboProperty(int space) {
        mouse_combo_space = space;
    }

    void Input::setMouseClickProperty(int space) {
        mouse_click_space = space;
    }

    void Input::getMouseRepeatProperty(int *skip, int *rate) {
        if (skip) *skip = mouse_repeat_skip;
        if (rate) *rate = mouse_repeat_rate;
    }

    void Input::getMouseComboProperty(int *space) {
        if (space) *space = mouse_combo_space;
    }

    void Input::getMouseClickProperty(int *space) {
        if (space) *space = mouse_click_space;
    }

    bool Input::toggle(KEY::CODE key) {
        return ToggleKeyState[(int) key];
    }

    bool Input::trigger(KEY::CODE key) {
        return KeyState[(int) key] && !PreKeyState[(int) key];
    }

    bool Input::trigger(const vector<KEY::CODE> &keys) {
        size_t last_key_i = 0;
        for (size_t i = 1; i < keys.size(); ++i) {
            if (!KeyState[(int) keys[i]])
                return false;
            else if (KeyTriggerFrame[(int) keys[i]][0] > KeyTriggerFrame[(int) keys[last_key_i]][0])
                last_key_i = i;
        }
        KEY::CODE key = keys[last_key_i];
        // just like single binomial
        return !PreKeyState[(int) key];
    }

    bool Input::press(KEY::CODE key) {
        return KeyState[(int) key];
    }

    bool Input::press(const vector<KEY::CODE> &keys) {
        for (KEY::CODE key : keys) {
            if (!KeyState[(int) key])
                return false;
        }
        return true;
    }

    bool Input::repeat(KEY::CODE key) {
        if (!KeyState[(int) key]) return false;
        int key_hold_times = input_frame - KeyTriggerFrame[(int) key][0];
        int repeat_base = key_repeat_rate * key_repeat_skip;
        return (key_hold_times == 0) ||
               (key_hold_times > repeat_base && key_hold_times % key_repeat_rate == 0);
    }

    bool Input::repeat(const vector<KEY::CODE> &keys) {
        size_t last_key_i = 0;
        for (size_t i = 1; i < keys.size(); ++i) {
            if (!KeyState[(int) keys[i]])
                return false;
            else if (KeyTriggerFrame[(int) keys[i]][0] > KeyTriggerFrame[(int) keys[last_key_i]][0])
                last_key_i = i;
        }
        KEY::CODE key = keys[last_key_i];
        // just like single repeat
        int key_hold_times = input_frame - KeyTriggerFrame[(int) key][0];
        int repeat_base = key_repeat_rate * key_repeat_skip;
        return (key_hold_times == 0) ||
               (key_hold_times > repeat_base && key_hold_times % key_repeat_rate == 0);
    }

    bool Input::combo(const vector<KEY::CODE> &keys) {
        unsigned int key_last_i[NUM_SCANCODES];
        memset(key_last_i, 0, sizeof(unsigned int) * NUM_SCANCODES);
        size_t next_key_i = keys.size() - 1;
        KEY::CODE next_key = keys[next_key_i];
        if (!KeyState[(int) next_key] || PreKeyState[(int) next_key])
            return false;
        int next_frame = KeyTriggerFrame[(int) next_key][key_last_i[(int) next_key]++];
        for (int i = (int) next_key_i - 1; i >= 0; --i) {
            KEY::CODE key = keys[i];
            if (key_last_i[(int) key] >= NUM_STORE) return false;
            int frame = KeyTriggerFrame[(int) key][key_last_i[(int) key]++];
            if (next_frame - frame > key_combo_space) return false;
            next_key = key;
            next_frame = frame;
        }
        return true;
    }

    int Input::release(KEY::CODE key) {
        if (PreKeyState[(int) key] && !KeyState[(int) key])
            return input_frame - KeyTriggerFrame[(int) key][0];
        else
            return 0;
    }

    bool Input::click(KEY::CODE key, unsigned int times) {
        unsigned int last_i = 0;
        if (!KeyState[(int) key] || PreKeyState[(int) key])
            return false;
        int next_frame = KeyTriggerFrame[(int) key][last_i++];
        while (--times > 0) {
            if (last_i >= NUM_STORE) return false;
            int frame = KeyTriggerFrame[(int) key][last_i++];
            if (next_frame - frame > key_click_space) return false;
            next_frame = frame;
        }
        return true;
    }

    KEY::CODE Input::single(const std::vector<KEY::CODE> &keys) {
        size_t i = 0;
        // 找到被按下的按键
        for (i = 0; i < keys.size(); ++i) {
            if (KeyState[(int) keys[i]])
                break;
        }
        // 如果没有被按下的按键
        if (i >= keys.size())
            return KEY::NONE;
        // 比较查找最后的按键
        KEY::CODE last_key = keys[i];
        for (i = i + 1; i < keys.size(); ++i) {
            if (KeyState[(int) keys[i]] && KeyTriggerFrame[(int) keys[i]][0] > KeyTriggerFrame[(int) last_key][0])
                last_key = keys[i];
        }
        // 返回最后的按键
        return last_key;
    }

    const Point<int> Input::mouse() {
        return MousePosition;
    }

    const Point<int> Input::relativeMouse() {
        return RelativeMousePosition;
    }

    bool Input::toggle(MOUSE::BUTTON button) {
        return ToggleMouseState[(int) button];
    }

    bool Input::trigger(MOUSE::BUTTON button) {
        return MouseState[(int) button] && !PreMouseState[(int) button];
    }

    bool Input::press(MOUSE::BUTTON button) {
        return MouseState[(int) button] != 0;
    }

    bool Input::repeat(MOUSE::BUTTON button) {
        if (!MouseState[(int) button]) return false;
        int mouse_hold_times = input_frame - MouseTriggerFrame[(int) button][0];
        int repeat_base = mouse_repeat_rate * mouse_repeat_skip;
        return (mouse_hold_times == 0) ||
               (mouse_hold_times > repeat_base && mouse_hold_times % mouse_repeat_rate == 0);
    }

    int Input::release(MOUSE::BUTTON button) {
        if (PreMouseState[(int) button] && !MouseState[(int) button])
            return input_frame - MouseTriggerFrame[(int) button][0];
        else
            return 0;
    }

    bool Input::click(MOUSE::BUTTON button, unsigned int times) {
        unsigned int last_i = 0;
        if (!MouseState[(int) button] || PreMouseState[(int) button])
            return false;
        int next_frame = MouseTriggerFrame[(int) button][last_i++];
        while (--times > 0) {
            if (last_i >= NUM_STORE) return false;
            int frame = MouseTriggerFrame[(int) button][last_i++];
            if (next_frame - frame > mouse_click_space) return false;
            next_frame = frame;
        }
        return true;
    }

    bool Input::comboEx(const std::vector<BUTTON> &buttons) {
        unsigned int key_last_i[NUM_SCANCODES];
        unsigned int mouse_last_i[NUM_MOUSE_BUTTON];
        memset(key_last_i, 0, sizeof(unsigned int) * NUM_SCANCODES);
        memset(mouse_last_i, 0, sizeof(unsigned int) * NUM_MOUSE_BUTTON);
        size_t next_button_i = buttons.size() - 1;
        BUTTON next_button = buttons[next_button_i];
        if (next_button.type == BUTTON_TYPE::KEY) {
            if (!KeyState[(int) next_button.key] || PreKeyState[(int) next_button.key])
                return false;
        } else {
            if (!MouseState[(int) next_button.button] || PreMouseState[(int) next_button.button])
                return false;
        }
        int next_frame = next_button.type == BUTTON_TYPE::KEY ?
                         KeyTriggerFrame[(int) next_button.key][key_last_i[(int) next_button.key]++] :
                         MouseTriggerFrame[(int) next_button.button][mouse_last_i[(int) next_button.button]++];
        for (int i = (int) next_button_i - 1; i >= 0; --i) {
            BUTTON button = buttons[i];
            if (button.type == BUTTON_TYPE::KEY) {
                if (key_last_i[(int) button.key] >= NUM_STORE) return false;
                int frame = KeyTriggerFrame[(int) button.key][key_last_i[(int) button.key]++];
                if (next_frame - frame > key_combo_space) return false;
                next_frame = frame;
            } else {
                if (mouse_last_i[(int) button.button] >= NUM_STORE) return false;
                int frame = MouseTriggerFrame[(int) button.button][mouse_last_i[(int) button.button]++];
                if (next_frame - frame > mouse_combo_space) return false;
                next_frame = frame;
            }
        }
        return true;
    }
}