//
// Created by kier on 15-11-18.
//

#include <SDL2/SDL_image.h>
#include "Window.h"
#include "Notifier.h"
#include "Util.h"

#include "Renderer.h"
#include "Rect.h"

#include <memory>

using namespace std;

namespace bud {
    Window::Window()
            : Window("Untitled") {
    }

    Window::Window(const std::string &title)
            : Window(title, 640, 480) {
    }

    Window::Window(const std::string &title, int w, int h)
            : Window(title, w, h, SDL_WINDOW_SHOWN) {
    }

    Window::Window(const std::string &title, int w, int h, unsigned int flags)
            : Window(title, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, w, h, flags) {
    }

    Window::Window(const std::string &title, int x, int y, int w, int h, unsigned int flags)
            : m_borrow(false) {
        m_window = SDL_CreateWindow(title.c_str(), x, y, w, h, flags);
        if (m_window == nullptr) {
            Notifier::err(B("Error: Create Window \"", title, "\" error: ", SDL_GetError()));
        }
    }

    Window::Window(SDL_Window *sdl_window)
            : m_borrow(true), m_window(sdl_window) {
    }

    Window::~Window() {
        if (m_bud_renderer != nullptr) {
            delete m_bud_renderer;
        }
        if (!m_borrow && m_window != nullptr) {
            SDL_DestroyWindow(m_window);
        }
    }

    Window::Window(Window &&borrow_window)
            : m_borrow(borrow_window.m_borrow), m_window(borrow_window.m_window),
              m_bud_renderer(borrow_window.m_bud_renderer) {
        // 该方法会取缔原窗口的权限管理，其仍然可以使用
        borrow_window.m_borrow = true;
        borrow_window.m_bud_renderer = nullptr;
    }

    SDL_Window *Window::meta_window() {
        return m_window;
    }

    bool Window::valid() const {
        return m_window != nullptr;
    }

    Renderer *Window::getRenderer() {
        if (m_bud_renderer != nullptr)
            return m_bud_renderer;
        else
            return newRenderer(SDL_RENDERER_ACCELERATED, -1);
    }

    Renderer *Window::newRenderer(unsigned int flags, int index) {
        // 如果是借来的数据是不推荐使用渲染器的，其行为还没有被详细测试
        // if (m_borrow) return nullptr;
        if (m_bud_renderer != nullptr) {
            delete m_bud_renderer;
            m_bud_renderer = nullptr;
        }
        SDL_Renderer *temp_renderer = SDL_CreateRenderer(m_window, index, flags);
        if (temp_renderer == nullptr) {
            Notifier::err(B("Error: Create Renderer error: ", SDL_GetError()));
        }
        m_bud_renderer = new Renderer(temp_renderer);
        return m_bud_renderer;
    }

    void Window::setTitle(const std::string &title) {
        SDL_SetWindowTitle(m_window, title.c_str());
    }

    void Window::setFullscreen(WINDOW_MODE flag) {
        switch (flag) {
            case WINDOW_MODE::WINDOWED:
                SDL_SetWindowFullscreen(m_window, 0);
                break;
            case WINDOW_MODE::FULLSCREEN:
                SDL_SetWindowFullscreen(m_window, SDL_WINDOW_FULLSCREEN);
                break;
            case WINDOW_MODE::FULLSCREEN_DESKTOP:
                SDL_SetWindowFullscreen(m_window, SDL_WINDOW_FULLSCREEN_DESKTOP);
                break;
        }
    }

    void Window::show() {
        SDL_ShowWindow(m_window);
    }

    void Window::hide() {
        SDL_HideWindow(m_window);
    }

    void Window::showCursor(bool toggle) {
        if (toggle)
            SDL_ShowCursor(SDL_ENABLE);
        else
            SDL_ShowCursor(SDL_DISABLE);
    }

    void Window::setIcon(const std::string &path) {
        SDL_Surface *iconSurface = IMG_Load(path.c_str());
        if (iconSurface == nullptr) {
            Notifier::err(B("Error: Load icon \"", path.c_str(), "\" error: ", IMG_GetError()));
        }
        else {
            SDL_SetWindowIcon(m_window, iconSurface);
            SDL_FreeSurface(iconSurface);
        }
    }

    const std::string Window::title() {
        return SDL_GetWindowTitle(m_window);
    }

    int Window::width() {
        int w, h;
        SDL_GetWindowSize(m_window, &w, &h);
        return w;
    }

    int Window::height() {
        int w, h;
        SDL_GetWindowSize(m_window, &w, &h);
        return h;
    }

    const Rect Window::rect() {
        int x, y, w, h;
        SDL_GetWindowPosition(m_window, &x, &y);
        SDL_GetWindowSize(m_window, &w, &h);
        return {x, y, w, h};
    }

    bool Window::cursor() {
        return SDL_ShowCursor(SDL_QUERY) == SDL_ENABLE;
    }

    unsigned int Window::id() {
        return SDL_GetWindowID(m_window);
    }

    Window Window::GetFromID(unsigned int window_id) {
        return move(Window(SDL_GetWindowFromID(window_id)));
    }

    Window Window::GetMouseFocus() {
        return move(Window(SDL_GetMouseFocus()));
    }
}