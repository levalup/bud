//
// Created by kier on 15-11-17.
//

#ifndef BUD_NODE_H
#define BUD_NODE_H

#include <functional>

namespace bud {

    class Node {
    public:
        virtual ~Node();

        using DeadHandler = std::function<void(Node *)>;

        virtual void update();

        virtual void render();

        virtual void handleUpdate();

        virtual void handleRender();

        bool dead();

        void kill();

        // void revive() { this->m_dead = false; }

        void selfDelete(bool toggle = true);

        static void Deleter(Node *node);

        DeadHandler deadHandler = nullptr;

        bool isActived() const;

        void active(bool actived = true);

        bool isShown() const;

        void show(bool shown = true);

        void forceUpdate();

        void forceRender();

        void *_alloc(size_t _size);

        void *_allocated_data();

        // 注意，这里返回的是申请空间的字节大小
        size_t allocated_size();

        template<typename T>
        inline T *alloc(size_t _size = 1) { return (T *) _alloc(sizeof(T) * _size); }

        template<typename T>
        inline T *allocated_data() { return (T *) _allocated_data(); }

    protected:
        bool m_actived = true;
        bool m_shown = true;
    private:
        bool m_dead = false;

        void *m_alloc = nullptr;
        size_t m_alloc_size = 0;
    };

}


#endif //BUD_NODE_H
