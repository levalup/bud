//
// Created by kier on 11/20/15.
//

#ifndef BUD_ANIMATIONMOTION_H
#define BUD_ANIMATIONMOTION_H

#include "Motion.h"
#include <functional>

namespace bud {

    enum class ANIMATION_LAYOUT {
        H, V
    };

    // 使用本类播放需要注意，要预先设定好Sprite.clip
    class AnimationMotion : public Motion {
    public:
        AnimationMotion(ANIMATION_LAYOUT layout, unsigned int max_frame, unsigned int step = 1, int max_times = -1);

        virtual void update(Sprite *sprite) override;

    private:
        ANIMATION_LAYOUT m_layout = ANIMATION_LAYOUT::H;
        unsigned int m_frame_index = 0;
        unsigned int m_max_frame;
        unsigned int m_step = 1;
        int m_max_times = -1;
        unsigned int m_update_times = 0;
    };

}


#endif //BUD_ANIMATIONMOTION_H
