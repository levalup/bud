//
// Created by kier on 11/24/15.
//

#include "LocalMotion.h"

namespace bud {

    void LocalMotion::whenUpdate(const UpdateHandler &handler) {
        this->m_update_hanlder = handler;
    }

    void LocalMotion::whenFinish(const FinishHandler &handler) {
        this->m_finish_hanlder = handler;
    }

    void LocalMotion::update(Sprite *sprite) {
        Motion::update(sprite);
        if (m_update_hanlder) m_update_hanlder(sprite);
    }

    void LocalMotion::onFinish() {
        Motion::onFinish();
        if (m_finish_hanlder) m_finish_hanlder();
    }
}