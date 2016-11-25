//
// Created by kier on 15-11-18.
//

#include "Rect.h"

#include "Point.h"

namespace bud {

    Rect::Rect() {
    }

    Rect::Rect(int w, int h)
            : w(w), h(h) {
    }

    Rect::Rect(int x, int y, int w, int h)
            : x(x), y(y), w(w), h(h) {
    }

    Rect::Rect(const SDL_Rect &rect)
            : Rect(rect.x, rect.y, rect.w, rect.h) {
    }

    Rect::Rect(const SDL_Rect *rect)
            : Rect(rect->x, rect->y, rect->w, rect->h) {
    }

    Rect::Rect(const Rect &other)
            : x(other.x), y(other.y), w(other.w), h(other.h) {
    }

    Rect &Rect::operator=(const Rect &rhs) {
        this->x = rhs.x;
        this->y = rhs.y;
        this->w = rhs.w;
        this->h = rhs.h;
        return *this;
    }

    void Rect::set(int x, int y, int w, int h) {
        this->x = x;
        this->y = y;
        this->w = w;
        this->h = h;
    }

    void Rect::raw_fill(SDL_Rect *sdl_rect) const {
        sdl_rect->x = x;
        sdl_rect->y = y;
        sdl_rect->w = w;
        sdl_rect->h = h;
    }

    const SDL_Rect Rect::meta_rect() const {
        SDL_Rect sdl_rect;
        sdl_rect.x = x;
        sdl_rect.y = y;
        sdl_rect.w = w;
        sdl_rect.h = h;
        return sdl_rect;
    }

    Rect::Rect(const Point<int> &size)
            : w(size.x), h(size.y) {

    }

    Rect::Rect(const Point<int> &head, const Point<int> &size)
            : x(head.x), y(head.y), w(size.x), h(size.y) {

    }

    const Point<int> Rect::head() const {
        return {x, y};
    }

    const Point<int> Rect::center() const {
        return {(x + x + w) / 2, (y + y + h) / 2};
    }

    const Point<int> Rect::tail() const {
        return {x + w, y + h};
    }

    const Point<int> Rect::size() const {
        return {w, h};
    }

    const Rect Rect::base() const {
        return {0, 0, w, h};
    }

    const Rect Rect::matrix(int row, int col) const {
        return {w * col, h * row, w, h};
    }

    const Rect Rect::row(int r) const {
        return {x, h * r, w, h};
    }

    const Rect Rect::col(int c) const {
        return {w * c, y, w, h};
    }

    const Rect Rect::clip(int row, int col) const {
        return {0, 0, w / col, h / row};
    }

    bool Rect::contain(const Point<int> &p) const {
        return x <= p.x && p.x <= x + w && y <= p.y && p.y <= y + h;
    }

    bool Rect::intersect(const Rect &rect) const {
        return this->intersect(&rect);
    }

    bool Rect::intersect(const Rect *rect) const {
        SDL_Rect A = this->meta_rect();
        SDL_Rect B = rect->meta_rect();
        return SDL_HasIntersection(&A, &B);
    }

    const Rect Rect::intersectRect(const Rect &rect) const {
        return this->intersectRect(&rect);
    }

    const Rect Rect::intersectRect(const Rect *rect) const {
        SDL_Rect A = this->meta_rect();
        SDL_Rect B = rect->meta_rect();
        SDL_Rect C;
        if (SDL_IntersectRect(&A, &B, &C)) {
            return C;
        }
        else {
            return {0, 0, 0, 0};
        }
    }

    Rect operator+(const Rect &r, const Point<int> &p) {
        return {r.x + p.x, r.y + p.y, r.w, r.h};
    }

    Rect operator+(const Point<int> &p, const Rect &r) {
        return {r.x + p.x, r.y + p.y, r.w, r.h};
    }

    Rect operator*(const Rect &r, double scalar) {
        return {(int) (r.x * scalar), (int) (r.y * scalar), (int) (r.w * scalar), (int) (r.h * scalar)};
    }

    Rect operator*(double scalar, const Rect &r) {
        return {(int) (r.x * scalar), (int) (r.y * scalar), (int) (r.w * scalar), (int) (r.h * scalar)};
    }

    Rect operator*(const Rect &r, const Point<double> &scalar) {
        return {(int) (r.x * scalar.x), (int) (r.y * scalar.y), (int) (r.w * scalar.x), (int) (r.h * scalar.y)};
    }

    Rect operator*(const Point<double> &scalar, const Rect &r) {
        return {(int) (r.x * scalar.x), (int) (r.y * scalar.y), (int) (r.w * scalar.x), (int) (r.h * scalar.y)};
    }

    Rect operator/(const Rect &r, double scalar) {
        return {(int) (r.x / scalar), (int) (r.y / scalar), (int) (r.w / scalar), (int) (r.h / scalar)};
    }

    Rect operator/(double scalar, const Rect &r) {
        return {(int) (scalar / r.x), (int) (scalar / r.y), (int) (scalar / r.w), (int) (scalar / r.h)};
    }

    Point<int> operator/(const Rect &r1, const Rect &r2) {
        return {r1.w / r2.w, r1.h / r2.h};
    }

    Rect operator/(const Rect &r, const Point<int> &p) {
        return {0, 0, r.w / p.x, r.h / p.y};
    }

    Rect operator%(const Rect &r1, const Rect &r2) {
        Point<int> full = r2 / r1;
        Point<int> frame = Rect(r1.tail()) / r1 - Point<int>(1, 1);
        Point<int> result;

        if (frame.x >= full.x) {
            if (frame.y >= full.y)   // 行和列都超出范围
            {
                result.x = frame.x % full.x;
                result.y = frame.y % full.y;
            }
            else    // 只有x超出范围
            {
                result.x = frame.x % full.x;
                result.y = (frame.y + frame.x / full.x) % full.y;
            }
        }
        else if (frame.y >= full.y)  // 只有y超出范围
        {
            result.x = (frame.x + frame.y / full.y) % full.x;
            result.y = frame.y % full.y;
        }
        else    // 只有x和y都没有超出范围
        {
            result = frame;
        }
        return r1.matrix(result.y, result.x);
    }

    std::ostream &operator<<(std::ostream &out, const Rect &r) {
        return out << "(" << r.x << ", " << r.y << ", " << r.w << ", " << r.h << ")";
    }
}