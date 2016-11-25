//
// Created by kier on 15-11-18.
//

#include "BUD.h"

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer.h>
#include "Util.h"
#include "Notifier.h"

namespace bud {
    BUD::BUD()
            : BUD(SDL_INIT_VIDEO | SDL_INIT_AUDIO, IMG_INIT_PNG) {
    }

    BUD::BUD(unsigned int base_flag, unsigned int image_flag)
            : m_base_flag(base_flag), m_image_flag(image_flag), m_failed(false) {
        //Initialize SDL
        if (SDL_Init(m_base_flag) < 0) {
            Notifier::err(B("Error: SDL could not initialize! SDL Error: ", SDL_GetError()));
            m_failed = true;
        }
        else {
            m_base_inited = true;
        }
        //Set texture filtering to linear
        if (!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1")) {
            Notifier::err("Warning: Linear texture filtering not enabled!");
        }
        //Initialize SDL_image
        if (IMG_Init(m_image_flag) ^ m_image_flag) {
            Notifier::err(B("Error: SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError()));
            m_failed = true;
        }
        else {
            m_image_inited = true;
        }
        //Initialize SDL_ttf
        if (TTF_Init() == -1) {
            Notifier::err(B("Error: SDL_ttf could not initialize! SDL_ttf Error: %s\n", TTF_GetError()));
            m_failed = true;
        }
        else {
            m_ttf_inited = true;
        }
        // INitialize SDL_mixer
        if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) {
            Notifier::err(B("Error: SDL_mixer could not initialize! SDL_mixer Error: %s\n", Mix_GetError()));
            m_failed = true;
        }
        else {
            m_mixer_inited = true;
        }
    }

    BUD::~BUD() {
        if (m_mixer_inited)
            Mix_Quit();
        if (m_ttf_inited)
            TTF_Quit();
        if (m_image_inited)
            IMG_Quit();
        if (m_base_inited)
            SDL_Quit();
    }

    bool BUD::failed() const {
        return m_failed;
    }

}