//
// Created by kier on 15-11-17.
//

#include "Util.h"

namespace bud {

    _RangeIterator::_RangeIterator(int value, int step_v)
            : m_value(value), m_step_v(step_v) {

    }

    bool _RangeIterator::operator!=(const _RangeIterator &other) const {
        if (m_step_v >= 0)
            return this->m_value < other.m_value;
        else
            return this->m_value > other.m_value;
    }

    int _RangeIterator::operator*() const {
        return m_value;
    }

    _RangeIterator &_RangeIterator::operator++() {
        m_value += m_step_v;
        return *this;
    }

    _Range::_Range(int end_v)
            : m_begin_v(0), m_end_v(end_v), m_step_v(end_v >= 0 ? 1 : -1) {
    }

    _Range::_Range(int begin_v, int end_v)
            : m_begin_v(begin_v), m_end_v(end_v), m_step_v(end_v >= begin_v ? 1 : -1) {
    }

    _Range::_Range(int begin_v, int end_v, int step_v)
            : m_begin_v(begin_v), m_end_v(end_v), m_step_v(step_v) {
    }

    _RangeIterator _Range::begin() const {
        return _RangeIterator(m_begin_v, m_step_v);
    }

    _RangeIterator _Range::end() const {
        return _RangeIterator(m_end_v, m_step_v);
    }

    _XRange::_XRange(int end_v)
            : m_begin_v(0), m_end_v(end_v), m_step_v(end_v >= 0 ? 1 : -1) {
    }

    _XRange::_XRange(int begin_v, int end_v)
            : m_begin_v(begin_v), m_end_v(end_v), m_step_v(end_v >= begin_v ? 1 : -1) {
    }

    _XRange::_XRange(int begin_v, int end_v, int step_v)
            : m_begin_v(begin_v), m_end_v(end_v), m_step_v(step_v) {
    }

    _RangeIterator _XRange::begin() const {
        return _RangeIterator(m_begin_v, m_step_v);
    }

    _RangeIterator _XRange::end() const {
        return _RangeIterator(m_step_v > 0 ? m_end_v + 1 : m_end_v - 1, m_step_v);
    }

    const char *str(DIRECTION dir) {
        switch (dir) {
            case DIRECTION::NONE:
                return "none";
            case DIRECTION::UP:
                return "up";
            case DIRECTION::LEFT:
                return "left";
            case DIRECTION::DOWN:
                return "down";
            case DIRECTION::RIGHT:
                return "right";
            case DIRECTION::OPPOSITE:
                return "opposite";
        }
        return nullptr;
    }
}