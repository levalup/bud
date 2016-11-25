//
// Created by kier on 11/20/15.
//

#include "Motion.h"
#include "Sprite.h"

namespace bud {

    Motion::Motion() {

    }

    Motion::~Motion() {
        this->clear();
        _alloc(0);
    }

    void Motion::update(Sprite *sprite) {
        sprite->pos += v;
        v += a;
        sprite->angle += angle_v;
        angle_v += angle_a;

        for (auto it = m_runing_motions.begin(); it != m_runing_motions.end();) {
            Motion *motion = *it;
            motion->update(sprite);
            if (motion->done()) {
                it = m_runing_motions.erase(it);
                // 这里调用结束就kill精灵的方法
                if (motion->m_finish_kill)
                    sprite->kill();
                if (motion->doneHandler) {
                    auto handler = motion->doneHandler;
                    handler(motion);
                }
            }
            else {
                ++it;
            }
        }
    }

    void Motion::onFinish() {
    }

    void Motion::run(Motion *action) {
        this->m_runing_motions.push_back(action);
    }

    bool Motion::done() {
        return this->m_done;
    }

    void Motion::finish() {
        this->m_done = true;
        this->onFinish();
    }

    void Motion::clear() {
        for (Motion *motion :this->m_runing_motions) {
            if (motion->doneHandler) {
                auto handler = motion->doneHandler;
                handler(motion);
            }
        }
        this->m_runing_motions.clear();
    }

    void Motion::selfDelete(bool toggle) {
        if (toggle)
            this->doneHandler = this->Deleter;
        else
            this->doneHandler = nullptr;
    }

    void Motion::Deleter(Motion *motion) {
        delete motion;
    }

    void Motion::finishKill(bool toggle) {
        this->m_finish_kill = toggle;
    }

    void *Motion::_alloc(size_t _size) {
        if (_size == 0) {
            if (m_alloc) free(m_alloc);
            m_alloc = nullptr;
        } else if (m_alloc) {
            m_alloc = realloc(m_alloc, _size);
        } else
            m_alloc = malloc(_size);
        m_alloc_size = _size;
        return m_alloc;
    }

    void *Motion::_allocated_data() {
        return m_alloc;
    }

    size_t Motion::allocated_size() {
        return m_alloc_size;
    }
}