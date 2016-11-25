//
// Created by kier on 15-11-18.
//

#ifndef BUD_RECT_H
#define BUD_RECT_H

#include <SDL2/SDL_rect.h>
#include <ostream>

namespace bud {

    template<typename T>
    class Point;

    class Rect {
    public:
        Rect();

        Rect(int w, int h);

        Rect(int x, int y, int w, int h);

        Rect(const SDL_Rect &rect);

        Rect(const SDL_Rect *rect);

        Rect(const Point<int> &size);

        Rect(const Point<int> &head, const Point<int> &size);

        Rect(const Rect &other);

        Rect &operator=(const Rect &other);

        void set(int x, int y, int w, int h);

        void raw_fill(SDL_Rect *sdl_rect) const;

        const SDL_Rect meta_rect() const;

        // [x, y]
        const Point<int> head() const;

        // [(x + x + w) / 2, (y + y + h) / 2]
        const Point<int> center() const;

        // [x + w, y + h]
        const Point<int> tail() const;

        // [w, h]
        const Point<int> size() const;

        // [0, 0, w, h]
        const Rect base() const;

        // [w * col, h * row, w, h]
        const Rect matrix(int row, int col) const;

        // [x, h * r, w, h]
        const Rect row(int r) const;

        // [w * c, y, w, h]
        const Rect col(int c) const;

        // [0, 0, w / col, h / row]
        const Rect clip(int row, int col) const;

        // return true if this contain the point
        bool contain(const Point<int> &p) const;

        // return true this intersect the "rect"
        bool intersect(const Rect &rect) const;

        // return true this intersect the "rect"
        bool intersect(const Rect *rect) const;

        // return then intersection between this and the "rect"
        const Rect intersectRect(const Rect &rect) const;

        // return then intersection between this and the "rect"
        const Rect intersectRect(const Rect *rect) const;

        int x = 0;
        int y = 0;
        int w = 0;
        int h = 0;
    protected:
    private:
    };

    // [x + p.x, y + p.y, w, h]
    Rect operator+(const Rect &r, const Point<int> &p);

    // [x + p.x, y + p.y, w, h]
    Rect operator+(const Point<int> &p, const Rect &r);

    // [x * scalar, y * scalar, w * scalar, h * scalar]
    Rect operator*(const Rect &r, double scalar);

    // [x * scalar, y * scalar, w * scalar, h * scalar]
    Rect operator*(double scalar, const Rect &r);

    // [x * s.x, y * s.y, w * s.x, h * s.y]
    Rect operator*(const Rect &r, const Point<double> &scalar);

    // [x * s.x, y * s.y, w * s.x, h * s.y]
    Rect operator*(const Point<double> &scalar, const Rect &r);

    // [x / scalar, y / scalar, w / scalar, h / scalar]
    Rect operator/(const Rect &r, double scalar);

    // [scalar / x, scalar / y, scalar / w, scalar / h]
    Rect operator/(double scalar, const Rect &r);

    // [r1.w / r2.w, r1.h / r2.h]
    Point<int> operator/(const Rect &r1, const Rect &r2);

    // [0, 0, w / p.x, h / p.y]
    Rect operator/(const Rect &r, const Point<int> &p);

    // 这里有必要说明一下矩阵求模的规则，这里的操作主要思考精灵图的操作，
    // 处理完毕后的要求是必满足在后面的矩形里，
    // 则处理精灵图(行动画)可以利用下面的式子运算：
    // src_rect.col(frame) % full_rect
    Rect operator%(const Rect &r1, const Rect &r2);

    std::ostream &operator<<(std::ostream &out, const Rect &r);
}

#endif //BUD_RECT_H
