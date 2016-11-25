//
// Created by kier on 15-11-18.
//

#ifndef BUD_SOUND_H
#define BUD_SOUND_H

#include <SDL2/SDL_mixer.h>
#include <string>

namespace bud {

    class Sound {
    public:
        Sound();

        Sound(const std::string &path);

        virtual ~Sound();

        Sound(const Sound &other) = delete;

        Sound &operator=(const Sound &other) = delete;

        Mix_Chunk *meta_chunk();

        bool valid() const;

        void dispose();

        bool hasDisposed() const;

        bool load(const std::string &path);

        void play();

        void play(int loops);

        void fadeIn(int loops, int ms);

        static int GlobalVolume(int vol);

        static void StopAll();

        static void FadeOutAll(int ms);

    protected:
        Sound(Mix_Chunk *chunk);

    private:
        Mix_Chunk *m_chunk;
        int m_channel;
    };

}


#endif //BUD_SOUND_H
