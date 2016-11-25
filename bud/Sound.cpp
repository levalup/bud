//
// Created by kier on 15-11-18.
//

#include "Sound.h"
#include "Util.h"
#include "Notifier.h"

namespace bud {
    Sound::Sound()
            : Sound(nullptr) {
    }

    Sound::Sound(Mix_Chunk *chunk)
            : m_chunk(chunk), m_channel(-1) {
    }

    Sound::Sound(const std::string &path)
            : m_chunk(nullptr), m_channel(-1) {
        load(path);
    }

    Sound::~Sound() {
        dispose();
    }

    Mix_Chunk *Sound::meta_chunk() {
        return m_chunk;
    }

    bool Sound::valid() const {
        return m_chunk != nullptr;
    }

    void Sound::dispose() {
        if (m_chunk != nullptr) {
            Mix_FreeChunk(m_chunk);
            m_chunk = nullptr;
        }
    }

    bool Sound::hasDisposed() const {
        return m_chunk == nullptr;
    }

    bool Sound::load(const std::string &path) {
        dispose();
        m_chunk = Mix_LoadWAV(path.c_str());
        if (m_chunk == nullptr) {
            Notifier::err(B("Error: Load sound \"", path.c_str(), "\" error: ", Mix_GetError()));
        }
        return m_chunk != nullptr;
    }

    void Sound::play() {
        m_channel = Mix_PlayChannel(-1, m_chunk, 0);
    }

    void Sound::play(int loops) {
        m_channel = Mix_PlayChannel(-1, m_chunk, loops);
    }

    void Sound::fadeIn(int loops, int ms) {
        m_channel = Mix_FadeInChannel(-1, m_chunk, loops, ms);
    }

    int Sound::GlobalVolume(int vol) {
        return Mix_Volume(-1, vol);
    }

    void Sound::StopAll() {
        Mix_HaltChannel(-1);
    }

    void Sound::FadeOutAll(int ms) {
        Mix_FadeOutChannel(-1, ms);
    }

}