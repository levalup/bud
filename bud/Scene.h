//
// Created by kier on 11/19/15.
//

#ifndef BUD_SCENE_H
#define BUD_SCENE_H

#include "NodeLayeredContainer.h"
#include "ComponentContainer.h"

#include <functional>

namespace bud {
    class Renderer;

    class RendererPointer;

    class Scene : public NodeLayeredContainer, public ComponentContainer {
    public:
        Scene(Renderer *bud_renderer);

        virtual ~Scene();

        unsigned int updateTimes();

        virtual void handleUpdate() override;

        virtual void onLoad();

        virtual void onShow();

        virtual void onHide();

        virtual void onExit();

        virtual void handleLoad();

        virtual void handleShow();

        virtual void handleHide();

        virtual void handleExit();

        bool backable();

        void back();

        Renderer *getRenderer();

    private:
        Renderer *m_bud_renderer;

        unsigned int m_update_times = 0;
        bool m_backable = false;
    };

}


#endif //BUD_SCENE_H
