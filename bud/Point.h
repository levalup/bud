//
// Created by kier on 15-11-18.
//

#ifndef BUD_POINT_H
#define BUD_POINT_H

#include <SDL2/SDL.h>
#include <ostream>

namespace bud {
    template<typename T>
    class Point {
    public:
        Point();

        template<typename T1, typename T2>
        Point(T1 x, T2 y);

        Point(const SDL_Point &point);

        Point(const SDL_Point *point);

        template<typename TA>
        Point(const Point<TA> &other);

        template<typename TA>
        Point &operator=(const Point<TA> &other);

        // 设置点的值
        void set(T x, T y);

        // 保存点值到SDL结构内
        void raw_fill(SDL_Point *sdl_point) const;

        // 返回一个SDL结构
        const SDL_Point meta_point() const;

        // x ^ 2 + y ^ 2
        T normSquared() const;

        // sqrt(x ^ 2 + y ^ 2)
        double norm() const;

        // [x, y] / sqrt(x ^ 2 + y ^ 2)
        const Point normalize() const;

        // [int(x), int(u)]
        const Point<int> i() const;

        // [x + p.x, y + p.y]
        template<typename TA>
        Point &operator+=(const Point<TA> &p);

        // [x - p.x, y - p.y]
        template<typename TA>
        Point &operator-=(const Point<TA> &p);

        // [x * scalar, y * scalar]
        Point &operator*=(double scalar);

        // [x / scalar, y / scalar]
        Point &operator/=(double scalar);

        // [-x, -y]
        Point operator-() const;

        T x = 0;
        T y = 0;
    protected:
    private:
    };

    // [pa.x + pb.x, pa.y + pb.y]
    template<typename T1, typename T2>
    Point<T1> operator+(const Point<T1> &pa, const Point<T2> &pb);

    // [pa.x - pb.x, pa.y - pb.y]
    template<typename T1, typename T2>
    Point<T1> operator-(const Point<T1> &pa, const Point<T2> &pb);

    // [pa.x * pb.x, pa.y * pb.y]
    template<typename T1, typename T2>
    Point<T1> operator*(const Point<T1> &pa, const Point<T2> &pb);

    // [pa.x / pb.x, pa.y / pb.y]
    template<typename T1, typename T2>
    Point<T1> operator/(const Point<T1> &pa, const Point<T2> &pb);

    // [pa.x * scalar, pa.y * scalar]
    template<typename T>
    Point<T> operator*(const Point<T> &p, double scalar);

    // [pa.x * scalar, pa.y * scalar]
    template<typename T>
    Point<T> operator*(double scalar, const Point<T> &p);

    // [pa.x / scalar, pa.y / scalar]
    template<typename T>
    Point<T> operator/(const Point<T> &p, double scalar);

    // [scalar / pa.x, scalar / pa.y]
    template<typename T>
    Point<T> operator/(double scalar, const Point<T> &p);

    // return true only if pa.x == pb.x && pa.y == pb.y
    template<typename T>
    bool operator==(const Point<T> &pa, const Point<T> &pb);

    // return true only if pa.x != pb.x || pa.y != pb.y
    template<typename T>
    bool operator!=(const Point<T> &pa, const Point<T> &pb);

    template<typename T>
    std::ostream &operator<<(std::ostream &out, const Point<T> &p);

    template<typename T>
    using Vector2D = Point<T>;

    template<typename T>
    Point<T>::Point() {
    }

    template<typename T>
    template<typename T1, typename T2>
    Point<T>::Point(T1 x, T2 y)
            : x((T) x), y((T) y) {
    }

    template<typename T>
    Point<T>::Point(const SDL_Point &point)
            : Point<T>((T) point.x, (T) point.y) {
    }

    template<typename T>
    Point<T>::Point(const SDL_Point *point)
            : Point((T) point->x, (T) point->y) {
    }

    template<typename T>
    template<typename TA>
    Point<T>::Point(const Point<TA> &other)
            : x((T) other.x), y((T) other.y) {

    }

    template<typename T>
    template<typename TA>
    Point<T> &Point<T>::operator=(const Point<TA> &other) {
        this->x = (T) other.x;
        this->y = (T) other.y;
        return *this;
    }

    template<typename T>
    void Point<T>::set(T x, T y) {
        this->x = x;
        this->y = y;
    }

    template<typename T>
    void Point<T>::raw_fill(SDL_Point *sdl_point) const {
        sdl_point->x = (int) x;
        sdl_point->y = (int) y;
    }

    template<typename T>
    const SDL_Point Point<T>::meta_point() const {
        SDL_Point sdl_point;
        sdl_point.x = (int) x;
        sdl_point.y = (int) y;
        return sdl_point;
    }

    template<typename T>
    T Point<T>::normSquared() const {
        return x * x + y * y;
    }

    template<typename T>
    double Point<T>::norm() const {
        return sqrt(x * x + y * y);
    }

    template<typename T>
    const Point<T> Point<T>::normalize() const {
        double n = this->norm();
        if (n == 0) {
            return {0, 0};
        }
        else {
            return *this / n;
        }
    }

    template<typename T>
    const Point<int> Point<T>::i() const {
        return {(int) (x), (int) (y)};
    }

    template<typename T>
    template<typename TA>
    Point<T> &Point<T>::operator+=(const Point<TA> &p) {
        x += (T) p.x;
        y += (T) p.y;
        return *this;
    }

    template<typename T>
    template<typename TA>
    Point<T> &Point<T>::operator-=(const Point<TA> &p) {
        x -= (T) p.x;
        y -= (T) p.y;
        return *this;
    }

    template<typename T>
    Point<T> &Point<T>::operator*=(double scalar) {
        x *= scalar;
        y *= scalar;
        return *this;
    }

    template<typename T>
    Point<T> &Point<T>::operator/=(double scalar) {
        x /= scalar;
        y /= scalar;
        return *this;
    }

    template<typename T>
    Point<T> Point<T>::operator-() const {
        return {-x, -y};
    }

    template<typename T1, typename T2>
    Point<T1> operator+(const Point<T1> &pa, const Point<T2> &pb) {
        return {(T1) (pa.x + pb.x), (T1) (pa.y + pb.y)};
    }

    template<typename T1, typename T2>
    Point<T1> operator-(const Point<T1> &pa, const Point<T2> &pb) {
        return {(T1) (pa.x - pb.x), (T1) (pa.y - pb.y)};
    }

    template<typename T1, typename T2>
    Point<T1> operator*(const Point<T1> &pa, const Point<T2> &pb) {
        return {(T1) (pa.x * pb.x), (T1) (pa.y * pb.y)};
    }

    template<typename T1, typename T2>
    Point<T1> operator/(const Point<T1> &pa, const Point<T2> &pb) {
        return {(T1) (pa.x / pb.x), (T1) (pa.y / pb.y)};
    }

    template<typename T>
    Point<T> operator*(const Point<T> &p, double scalar) {
        return {(T) (p.x * scalar), (T) (p.y * scalar)};
    }

    template<typename T>
    Point<T> operator*(double scalar, const Point<T> &p) {
        return {(T) (p.x * scalar), (T) (p.y * scalar)};
    }

    template<typename T>
    Point<T> operator/(const Point<T> &p, double scalar) {
        return {(T) (p.x / scalar), (T) (p.y / scalar)};
    }

    template<typename T>
    Point<T> operator/(double scalar, const Point<T> &p) {
        return {(T) (scalar / p.x), (T) (scalar / p.y)};
    }

    template<typename T>
    bool operator==(const Point<T> &pa, const Point<T> &pb) {
        return pa.x == pb.x && pa.y == pb.y;
    }

    template<typename T>
    bool operator!=(const Point<T> &pa, const Point<T> &pb) {
        return pa.x != pb.x || pa.y != pb.y;
    }

    template<typename T>
    std::ostream &operator<<(std::ostream &out, const Point<T> &p) {
        return out << "(" << p.x << ", " << p.y << ")";
    }

}


#endif //BUD_POINT_H
