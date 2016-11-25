//
// Created by kier on 15-11-18.
//

#include "Music.h"
#include "Notifier.h"
#include "Util.h"

namespace bud {
    Music::Music()
            : Music(nullptr) {
    }

    Music::Music(Mix_Music *music)
            : m_music(music) {
    }

    Music::Music(const std::string &path)
            : m_music(nullptr) {
        load(path);
    }

    Music::~Music() {
        dispose();
    }

    Mix_Music *Music::meta_music() {
        return m_music;
    }

    bool Music::valid() const {
        return m_music != nullptr;
    }

    void Music::dispose() {
        if (m_music != nullptr) {
            Mix_FreeMusic(m_music);
            m_music = nullptr;
        }
    }

    bool Music::hasDisposed() const {
        return m_music == nullptr;
    }

    bool Music::load(const std::string &path) {
        dispose();
        m_music = Mix_LoadMUS(path.c_str());
        if (m_music == nullptr) {
            Notifier::err(B("Error: Load music \"", path.c_str(), "\" error: ", Mix_GetError()));
        }
        return m_music != nullptr;
    }

    void Music::play() {
        Mix_PlayMusic(m_music, 1);
    }

    void Music::play(int times) {
        Mix_PlayMusic(m_music, times);
    }

    void Music::fadeIn(int ms) {
        Mix_FadeInMusic(m_music, 1, ms);
    }

    void Music::fadeIn(int times, int ms) {
        Mix_FadeInMusic(m_music, times, ms);
    }

    void Music::fadeOut(int ms) {
        Mix_FadeOutMusic(ms);
    }

    void Music::pause() {
        Mix_PauseMusic();
    }

    void Music::resume() {
        Mix_ResumeMusic();
    }

    void Music::stop() {
        Mix_HaltMusic();
    }

    bool Music::playing() {
        return (bool) Mix_PlayingMusic();
    }

    bool Music::paused() {
        return (bool) Mix_PausedMusic();
    }

    int Music::GlobalVolume(int vol) {
        return Mix_VolumeMusic(vol);
    }

    void Music::FadeOut(int ms) {
        Mix_FadeOutMusic(ms);
    }

    void Music::Pause() {
        Mix_PauseMusic();
    }

    void Music::Resume() {
        Mix_ResumeMusic();
    }

    void Music::Stop() {
        Mix_HaltMusic();
    }

    bool Music::Playing() {
        return (bool) Mix_PlayingMusic();
    }

    bool Music::Paused() {
        return (bool) Mix_PausedMusic();
    }
}