//
// Created by kier on 15-11-17.
//

#include "Notifier.h"
#include "Util.h"

#include <cstdio>
#include <SDL2/SDL.h>

namespace bud {

    const std::string Notifier::version() {
        return "0.0.2";
    }

    const std::string Notifier::meta_version() {
        SDL_version compiled;
        SDL_version linked;
        SDL_VERSION(&compiled);
        SDL_GetVersion(&linked);
        return B("SDL ", (int)compiled.major, ".", (int)compiled.minor, ".", (int)compiled.patch, " -> ",
                 (int)linked.major, ".", (int)linked.minor, ".", (int)linked.patch);
    }

    void Notifier::log(const std::string &msg) {
        printf("%s\n", msg.c_str());
    }

    void Notifier::err(const std::string &msg) {
        log(msg);
        message(MESSAGEBOX_TYPE::ERROR, "Error", msg);
    }

    void Notifier::message(MESSAGEBOX_TYPE type, const std::string &title, const std::string &msg) {
        switch (type) {
            case MESSAGEBOX_TYPE::ERROR:
                SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, title.c_str(), msg.c_str(), nullptr);
                break;
            case MESSAGEBOX_TYPE::WARNING:
                SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_WARNING, title.c_str(), msg.c_str(), nullptr);
                break;
            case MESSAGEBOX_TYPE::INFORMATION:
                SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_INFORMATION, title.c_str(), msg.c_str(), nullptr);
                break;
        }
    }

    void Notifier::message(const std::string &title, const std::string &msg) {
        message(MESSAGEBOX_TYPE::INFORMATION, title, msg);
    }
}