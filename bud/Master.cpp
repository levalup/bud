//
// Created by kier on 11/19/15.
//

#include "Master.h"
#include "Renderer.h"
#include "Color.h"
#include "Point.h"
#include "Input.h"

#include <vector>
#include <list>
#include <iostream>

using namespace std;

namespace bud {

    Master::Master(Renderer *bud_renderer)
            : m_bud_renderer(bud_renderer) {
        this->setFPS(60);
    }

    Master::~Master() {
    }

    unsigned int Master::updateTimes() {
        return this->m_update_times;
    }

    void Master::init() {
        this->m_update_times = 0;
        this->m_frame_count = 0;

        // for frame delay
        this->m_local_frame_count = 0;
        this->m_local_frame_base_ticks = SDL_GetTicks();

        // for caculate FPS
        this->m_second_ago_count = 0;
        this->m_second_ago_ticks = SDL_GetTicks();

    }

    void Master::loop() {
        this->init();
        Input::init();
        while (!this->dead()) {
            // pump event for handling
            EventListener::PumpEvent();
            // input
            EventListener::PullEvent(this);
            // handle input without event
            Input::update();
            // update
            this->handleUpdate();   // this can be overrided
            this->m_update_times++;
            // render
            this->m_bud_renderer->clear(Color::White);
            this->handleRender();   // this can be overrided
            this->renderFPS();
            // delay
            this->delay();
            // draw
            this->m_bud_renderer->render();
            this->m_frame_count++;
            this->calculateFPS();
        }
    }

    void Master::delay() {
        this->m_local_frame_count++;
        unsigned int current_ticks = SDL_GetTicks();
        unsigned int target_ticks =
                this->m_local_frame_base_ticks + (unsigned int) (this->m_local_frame_count * 1000.0 / this->m_fps);
        if (current_ticks <= target_ticks) {
            SDL_Delay(target_ticks - current_ticks);
        } else {
            this->m_local_frame_count = 0;
            this->m_local_frame_base_ticks = SDL_GetTicks();
        }
    }

    void Master::calculateFPS() {
        unsigned int now_count = m_frame_count;
        unsigned int now_ticks = SDL_GetTicks();
        if (now_ticks - m_second_ago_ticks >= 1000) {
            m_real_fps = (unsigned int) floor(
                    1000.0 * (now_count - m_second_ago_count) / (now_ticks - m_second_ago_ticks) + 0.5);
            m_second_ago_count = now_count;
            m_second_ago_ticks = now_ticks;
        }
    }

    int _Master_renderFPS(Renderer *bud_renderer, unsigned int fps, int x, int y);

    void Master::renderFPS() {
        if (this->m_show_fps) {
            this->m_bud_renderer->setDrawColor(Color::Green);
            _Master_renderFPS(this->m_bud_renderer, this->m_real_fps, 7, 7);
        }
    }

    void Master::showFPS(bool toggle) {
        this->m_show_fps = toggle;
    }

    void Master::setFPS(unsigned int fps) {
        this->m_fps = fps;
        this->m_real_fps = this->m_fps;
    }

    unsigned int Master::getFPS() {
        return this->m_fps;
    }

    Renderer *Master::getRenderer() {
        return this->m_bud_renderer;
    }

    vector<list<Point<int>>> _Master_num = {
            {{0, 0}, {4, 0}, {4, 8}, {0, 8}, {0, 0}},
            {{4, 0}, {4, 4}, {4, 8}},
            {{0, 0}, {4, 0}, {4, 4}, {0, 4}, {0, 8}, {4, 8}},
            {{0, 0}, {4, 0}, {4, 4}, {0, 4}, {4, 4}, {4, 8}, {0, 8}},
            {{0, 0}, {0, 4}, {4, 4}, {4, 0}, {4, 8}},
            {{4, 0}, {0, 0}, {0, 4}, {4, 4}, {4, 8}, {0, 8}},
            {{4, 0}, {0, 0}, {0, 8}, {4, 8}, {4, 4}, {0, 4}},
            {{0, 0}, {4, 0}, {4, 8}},
            {{0, 4}, {0, 0}, {4, 0}, {4, 8}, {0, 8}, {0, 4}, {4, 4}},
            {{4, 4}, {0, 4}, {0, 0}, {4, 0}, {4, 8}, {0, 8}}
    };

// 绘制FPS，返回值为接下来要绘制的位置，递归使用
    int _Master_renderFPS(Renderer *bud_renderer, unsigned int fps, int x, int y) {
        unsigned int now_num = fps % 10;
        unsigned int post_num = fps / 10;
        if (post_num > 0) {
            x = _Master_renderFPS(bud_renderer, post_num, x, y);
        }
        bud_renderer->line(_Master_num[now_num], {x, y});
        return x + 7;
    }
}
