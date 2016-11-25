//
// Created by kier on 11/20/15.
//

#include "AnimationMotion.h"
#include "Sprite.h"
#include "Texture.h"

namespace bud {

    AnimationMotion::AnimationMotion(ANIMATION_LAYOUT layout, unsigned int max_frame, unsigned int step, int max_times)
            : m_layout(layout), m_max_frame(max_frame), m_step(step), m_max_times(max_times) {
    }

    void AnimationMotion::update(Sprite *sprite) {
        Motion::update(sprite);

        // m_step times to through
        if (m_update_times % m_step) {
            m_update_times++;
            return;
        } else {
            m_update_times++;
        }

        if (sprite->texture() == nullptr ||
            (m_max_times >= 0 && m_frame_index >= m_max_frame * m_max_times)) {
            this->finish();
            return;
        }

        switch (this->m_layout) {
            case ANIMATION_LAYOUT::H:
                sprite->clip = sprite->clip.base().col(m_frame_index % m_max_frame) % sprite->texture()->rect();
                break;
            case ANIMATION_LAYOUT::V:
                sprite->clip = sprite->clip.base().row(m_frame_index % m_max_frame) % sprite->texture()->rect();
                break;
        }
        this->m_frame_index++;
    }
}
