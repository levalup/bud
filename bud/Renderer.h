//
// Created by kier on 15-11-18.
//

#ifndef BUD_RENDERER_H
#define BUD_RENDERER_H

#include <SDL2/SDL_render.h>
#include <list>
#include <string>
#include "Util.h"

namespace bud {

    class Texture;

    template<typename T>
    class Point;

    class Rect;

    class Font;

    class Color;

    enum class FLIP {
        NONE = 0,
        H = 1,
        V = 2,
        H_V = 3
    };

    class Renderer {
    public:
        virtual ~Renderer();

        Renderer(const Renderer &other) = delete;

        Renderer &operator=(const Renderer &other) = delete;

        SDL_Renderer *meta_renderer();

        bool valid() const;

        void dispose();

        bool hasDisposed() const;

        void render();

        Texture *setTarget(Texture *texture);

        Texture *setTargetDefault();

        Texture *target();

        void setDrawColor(byte r, byte g, byte b, byte a);

        void setDrawColor(const Color &color);

        const Color drawColor();

        void clear();

        void clear(byte r, byte g, byte b, byte a);

        void clear(const Color &color);

        void copy(Texture *texture);

        void copy(Texture *texture, int x, int y);

        void copy(Texture *texture, const Point<int> &dest);

        void copy(Texture *texture, const Rect &dest);

        void copy(Texture *texture, const Rect &src, const Rect &dest);

        void copyEx(Texture *texture, const Rect &srcrect, const Rect &dstrect, double angle, const Point<int> &center,
                    bool flip_H, bool flip_V);

        void copyEx(Texture *texture, const Rect &srcrect, const Rect &dstrect, double angle, const Point<int> &center,
                    FLIP flip_flag);

        void line(const Point<int> &p1, const Point<int> &p2);

        void line(const std::list<Point<int>> &ps);

        void line(const std::list<Point<int>> &ps, const Point<int> &base);

        void point(const Point<int> &p);

        void point(const std::list<Point<int>> &ps);

        void point(const std::list<Point<int>> &ps, const Point<int> &base);

        void rect(const Rect &r);

        void rect(const std::list<Rect> &rs);

        void rect(const std::list<Rect> &rs, const Point<int> &base);

        void fill(const Rect &r);

        void fill(const std::list<Rect> &rs);

        void fill(const std::list<Rect> &rs, const Point<int> &base);

        void text(const std::string &str, Font *font, int x, int y);

        void text(const std::string &str, Font *font, int x, int y, byte r, byte g, byte b);

        void text(const std::string &str, Font *font, int x, int y, const Color &color);

    protected:
        friend class Window;

        Renderer();

        Renderer(SDL_Renderer *renderer);

    private:
        SDL_Renderer *m_renderer;

        Texture *m_bud_texture;
    };

}


#endif //BUD_RENDERER_H
