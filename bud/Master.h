//
// Created by kier on 11/19/15.
//

#ifndef BUD_MASTER_H
#define BUD_MASTER_H

#include "NodeContainer.h"
#include "ComponentContainer.h"

namespace bud {
    class Renderer;

    class RendererPointer;

    class Master : public NodeContainer, public ComponentContainer {
    public:
        Master(Renderer *bud_renderer);

        virtual ~Master();

        unsigned int updateTimes();

        void init();

        void loop();

        void delay();

        void calculateFPS();

        void renderFPS();

        void showFPS(bool toggle);

        void setFPS(unsigned int fps);

        unsigned int getFPS();

        Renderer *getRenderer();

    private:
        Renderer *m_bud_renderer;
        unsigned int m_update_times;
        unsigned int m_frame_count;


        unsigned int m_fps;

        unsigned int m_local_frame_count;
        unsigned int m_local_frame_base_ticks;

        unsigned int m_real_fps;
        unsigned int m_second_ago_count;
        unsigned int m_second_ago_ticks;
        bool m_show_fps = false;
    };

}


#endif //BUD_MASTER_H
