//
// Created by kier on 11/24/15.
//

#ifndef BUD_LOCALMOTION_H
#define BUD_LOCALMOTION_H

#include "Motion.h"
#include <functional>

namespace bud {

    class LocalMotion : public Motion {
    public:
        using UpdateHandler = std::function<void(Sprite *)>;
        using FinishHandler = std::function<void()>;

        void whenUpdate(const UpdateHandler &handler);

        void whenFinish(const FinishHandler &handler);

        virtual void update(Sprite *sprite) override ;

        virtual void onFinish() override ;

    private:
        UpdateHandler m_update_hanlder = nullptr;
        FinishHandler m_finish_hanlder = nullptr;
    };

}


#endif //BUD_LOCALMOTION_H
