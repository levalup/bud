//
// Created by kier on 15-11-18.
//

#ifndef BUD_FONT_H
#define BUD_FONT_H

#include <SDL2/SDL_ttf.h>
#include <string>

namespace bud {

    class Font {
    public:
        Font();

        Font(const std::string &path, int ptsize);

        virtual ~Font();

        Font(const Font &other) = delete;

        Font &operator=(const Font &other) = delete;

        TTF_Font *meta_font();

        bool valid() const;

        void dispose();

        bool hasDisposed() const;

        bool load(const std::string &path, int ptsize);

        int font_size();

    protected:
        Font(TTF_Font *font);

    private:
        TTF_Font *m_font;
        int m_font_size;

        static TTF_Font *raw_open_font(const std::string &path, int ptsize);
    };

}


#endif //BUD_FONT_H
