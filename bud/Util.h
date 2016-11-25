//
// Created by kier on 15-11-17.
//

#ifndef BUD_UTIL_H
#define BUD_UTIL_H

#include <ostream>
#include <sstream>
#include <memory>

namespace bud {

    typedef unsigned char byte;

    inline void _B_str(std::ostream &out) { }

    // there is no error anyway, this is a new feature about C++11
    template<typename T, typename... Args>
    inline void _B_str(std::ostream &out, const T &t, Args... args) { _B_str(out << t, args...); }

    template<typename... Args>
    inline const std::string B(Args... args) {
        std::ostringstream oss;
        _B_str(oss, args...);
        return std::move(oss.str());
    }

    template<typename T>
    using _Dp = std::shared_ptr<T>;

    class _RangeIterator {
    public:
        explicit _RangeIterator(int value, int step_v);

        bool operator!=(const _RangeIterator &other) const;

        int operator*() const;

        _RangeIterator &operator++();

    private:
        int m_value;
        int m_step_v;
    };

    class _Range {
    public:
        _Range(int end_v);

        _Range(int begin_v, int end_v);

        _Range(int begin_v, int end_v, int step_v);

        _RangeIterator begin() const;

        _RangeIterator end() const;

    private:
        int m_begin_v;
        int m_end_v;
        int m_step_v;
    };

    class _XRange {
    public:
        _XRange(int end_v);

        _XRange(int begin_v, int end_v);

        _XRange(int begin_v, int end_v, int step_v);

        _RangeIterator begin() const;

        _RangeIterator end() const;

    private:
        int m_begin_v;
        int m_end_v;
        int m_step_v;
    };

    using range = _Range;
    using xrange = _XRange;

    enum class DIRECTION {
        NONE = 0,
        UP = 1,
        LEFT = 2,
        DOWN = 3,
        RIGHT = 4,
        OPPOSITE = 5
    };

    const char *str(DIRECTION dir);
}

#endif //BUD_UTIL_H
