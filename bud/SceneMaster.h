//
// Created by kier on 11/19/15.
//

#ifndef BUD_SCENEMASTER_H
#define BUD_SCENEMASTER_H

#include <stack>
#include "Master.h"

namespace bud {
    class RendererPointer;

    class Scene;

    class SceneMaster : public Master {
    public:
        SceneMaster(Renderer *bud_renderer);

        virtual ~SceneMaster();

        Scene *pushScene(Scene *stage);

        Scene *popScene();

        Scene *topScene();

        void clearScene();

        void activeScene(Scene *stage);

        unsigned long countScene();

        virtual void handleUpdate() override;

        virtual void handleRender() override;

        virtual void handleKeyDown(const KeyboardEvent &event) override;

        virtual void handleKeyUp(const KeyboardEvent &event) override;

        virtual void handleKeyRepeat(const KeyboardEvent &event) override;

        virtual void handleMouseMove(const MouseEvent &event) override;

        virtual void handleMouseButtonDown(const MouseEvent &event) override;

        virtual void handleMouseButtonUp(const MouseEvent &event) override;

        virtual void handleMouseButtonClick(const MouseEvent &event) override;

        virtual void handleMouseButtonDoubleClick(const MouseEvent &event) override;

        virtual void handleMouseWheelScroll(const MouseEvent &event) override;

        virtual void handleWindowMotion(const WindowEvent &event) override;

        virtual void handleQuit() override final;

    private:
        void updateTopScene();

        void renderTopScene();

        std::stack<Scene *> m_stack_scene;
    };
}

#endif //BUD_SCENEMASTER_H
