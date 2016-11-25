//
// Created by kier on 11/20/15.
//

#ifndef BUD_MOTION_H
#define BUD_MOTION_H

#include "Point.h"
#include <list>
#include <functional>

namespace bud {

    class Sprite;

    class Motion {
    public:
        Motion();

        virtual ~Motion();

        // 这里更新精灵的动作
        virtual void update(Sprite *sprite);

        // 动作结束后调用，注意，这个函数只有在finishi方法才会调用的
        virtual void onFinish();

        // 执行动作直到完成
        void run(Motion *action);

        // 返回动作是否完成
        bool done();

        // 设置动作完成，其中会调用onFinish方法
        void finish();

        // 设置未完成，不建议调用
        // void start() { this->m_done = false; }

        // 强制完成所有动作，不会触发finish事件
        void clear();

        void selfDelete(bool toggle = true);

        static void Deleter(Motion *motion);

        using DoneHandler = std::function<void(Motion *)>;

        DoneHandler doneHandler = nullptr;

        // 动作完成后判断是否要杀掉精灵，注意，这里在motion更新循环中才会kill精灵，
        void finishKill(bool toggle = true);

        Point<double> v = {0, 0};
        Point<double> a = {0, 0};

        double angle_v = 0;
        double angle_a = 0;

        void *_alloc(size_t _size);

        void *_allocated_data();

        size_t allocated_size();

        template<typename T>
        inline T *alloc(size_t _size = 1) { return (T *) _alloc(sizeof(T) * _size); }

        template<typename T>
        inline T *allocated_data() { return (T *) _allocated_data(); }
    private:
        bool m_done = false;
        std::list<Motion *> m_runing_motions;
        bool m_finish_kill = false;

        void *m_alloc = nullptr;
        size_t m_alloc_size = 0;
    };
}


#endif //BUD_MOTION_H
