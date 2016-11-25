//
// Created by kier on 15-11-18.
//

#ifndef BUD_TEXTURE_H
#define BUD_TEXTURE_H


#include <SDL2/SDL_render.h>
#include <SDL2/SDL_ttf.h>
#include <string>
#include "Util.h"

namespace bud {
    class Renderer;

    class RendererPointer;

    class Color;

    class Font;

    class Rect;

    enum class RENDER_TTF {
        SOLID,
        SHADED,
        BLENDED,
        //BLENDED_WRAPPED_RENDER
    };

    class Texture {
    public:
        Texture(Renderer *bud_renderer);

        Texture(Renderer *bud_renderer, const std::string &path);

        Texture(Renderer *bud_renderer, const std::string &path, byte r, byte g, byte b);

        Texture(Renderer *bud_renderer, const std::string &path, const Color &color);

        Texture(Renderer *bud_renderer, int w, int h);

        Texture(Renderer *bud_renderer, Font *font, const std::string &text,
                RENDER_TTF type = RENDER_TTF::BLENDED);

        Texture(Renderer *bud_renderer, Font *font, const std::string &text, byte r, byte g, byte b,
                RENDER_TTF type = RENDER_TTF::BLENDED);

        Texture(Renderer *bud_renderer, Font *font, const std::string &text, const Color &color,
                RENDER_TTF type = RENDER_TTF::BLENDED);

        virtual ~Texture();

        Texture(const Texture &other) = delete;

        Texture &operator=(const Texture &other) = delete;

        SDL_Texture *meta_texture();

        bool valid() const;

        void dispose();

        bool hasDisposed() const;

        bool create(int w, int h);

        bool load(const std::string &path);

        bool load(const std::string &path, byte r, byte g, byte b);

        bool load(const std::string &path, const Color &color);

        bool load(Font *font, const std::string &text, RENDER_TTF type);

        bool load(Font *font, const std::string &text, byte r, byte g, byte b, RENDER_TTF type);

        bool load(Font *font, const std::string &text, const Color &color, RENDER_TTF type);

        Renderer *getRenderer();

        const Rect rect();

        void setColorMod(const Color &color);

        const Color getColorMod();

        void setAlphaMod(byte alpha);

        byte getAlphaMod();

        void setMod(const Color &color);

        const Color getMod();

        int width();

        int height();

    protected:
        Texture(Renderer *bud_renderer, SDL_Texture *texture);

    private:
        Renderer *m_bud_renderer;
        SDL_Texture *m_texture;
        int m_width;
        int m_height;

        SDL_Texture *raw_image_load(const std::string &path, int flag, Uint8 r, Uint8 g, Uint8 b) const;

        SDL_Texture *raw_create_texture(int w, int h) const;

        SDL_Texture *raw_text_texture(const std::string &text, TTF_Font *font, SDL_Color fg, RENDER_TTF type) const;
    };

}


#endif //BUD_TEXTURE_H
