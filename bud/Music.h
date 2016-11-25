//
// Created by kier on 15-11-18.
//

#ifndef BUD_MUSIC_H
#define BUD_MUSIC_H


#include <SDL2/SDL_mixer.h>
#include <string>

namespace bud {

    class Music {
    public:
        Music();

        Music(const std::string &path);

        virtual ~Music();

        Music(const Music &other) = delete;

        Music &operator=(const Music &other) = delete;

        Mix_Music *meta_music();

        bool valid() const;

        void dispose();

        bool hasDisposed() const;

        bool load(const std::string &path);

        void play();

        void play(int times);

        void fadeIn(int ms);

        void fadeIn(int times, int ms);

        void fadeOut(int ms);

        void pause();

        void resume();

        void stop();

        bool playing();

        bool paused();

        static int GlobalVolume(int vol);

        static void FadeOut(int ms);

        static void Pause();

        static void Resume();

        static void Stop();

        static bool Playing();

        static bool Paused();

    protected:
        Music(Mix_Music *music);

    private:
        Mix_Music *m_music;
    };

}


#endif //BUD_MUSIC_H
