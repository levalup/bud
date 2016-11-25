//
// Created by kier on 11/19/15.
//

#include "SceneMaster.h"

#include "Scene.h"

namespace bud {

    SceneMaster::SceneMaster(Renderer *bud_renderer)
            : Master(bud_renderer) {
    }

    SceneMaster::~SceneMaster() {
        // this->clearScene();
    }

    Scene *SceneMaster::pushScene(Scene *stage) {
        Scene *old_stage = nullptr;
        if (!m_stack_scene.empty()) {
            old_stage = m_stack_scene.top();
            old_stage->handleHide();
        }
        stage->handleLoad();
        stage->handleShow();
        m_stack_scene.push(stage);
        return old_stage;
    }

    Scene *SceneMaster::popScene() {
        Scene *pop_stage = nullptr;
        if (!m_stack_scene.empty()) {
            pop_stage = m_stack_scene.top();
            pop_stage->handleHide();
            pop_stage->handleExit();
            m_stack_scene.pop();
            if (!m_stack_scene.empty()) {
                Scene *top_stage = m_stack_scene.top();
                top_stage->handleShow();
            }
        }
        return pop_stage;

    }

    Scene *SceneMaster::topScene() {
        Scene *top_stage = nullptr;
        if (!m_stack_scene.empty()) {
            top_stage = m_stack_scene.top();
        }
        return top_stage;
    }

    void SceneMaster::clearScene() {
        while (!m_stack_scene.empty()) {
            popScene();
        }
    }

    void SceneMaster::activeScene(Scene *stage) {
        while (!m_stack_scene.empty() && topScene() != stage) {
            popScene();
        }
        if (topScene() == nullptr) {
            pushScene(stage);
        }
    }

    unsigned long SceneMaster::countScene() {
        return this->m_stack_scene.size();
    }

    void SceneMaster::handleUpdate() {
        if (this->m_preorder_base_node) {
            Master::handleUpdate();
            this->updateTopScene();
        }
        else {
            this->updateTopScene();
            Master::handleUpdate();
        }
    }

    void SceneMaster::handleRender() {
        if (this->m_preorder_base_node) {
            Master::handleRender();
            this->renderTopScene();
        }
        else {
            this->renderTopScene();
            Master::handleRender();
        }
    }

    void SceneMaster::updateTopScene() {
        if (m_stack_scene.empty()) {
            kill();
        }
        else {
            Scene *top_scene = m_stack_scene.top();
            // 采用先更新，后检测是否返回，这样在场景的update里处理场景返回操作，
            top_scene->handleUpdate();
            if (top_scene->backable()) {
                popScene();
            }
        }
    }

    void SceneMaster::renderTopScene() {
        if (m_stack_scene.empty()) {
            // do nothing here
        }
        else {
            Scene *top_scene = m_stack_scene.top();
            top_scene->handleRender();
        }
    }

    void SceneMaster::handleKeyDown(const KeyboardEvent &event) {
        Master::handleKeyDown(event);
        Scene *top_stage = topScene();
        if (top_stage) {
            top_stage->handleKeyDown(event);
        }
    }

    void SceneMaster::handleKeyUp(const KeyboardEvent &event) {
        Master::handleKeyUp(event);
        Scene *top_stage = topScene();
        if (top_stage) {
            top_stage->handleKeyUp(event);
        }
    }

    void SceneMaster::handleKeyRepeat(const KeyboardEvent &event) {
        Master::handleKeyRepeat(event);
        Scene *top_stage = topScene();
        if (top_stage) {
            top_stage->handleKeyRepeat(event);
        }
    }

    void SceneMaster::handleMouseMove(const MouseEvent &event) {
        Master::handleMouseMove(event);
        Scene *top_stage = topScene();
        if (top_stage) {
            top_stage->handleMouseMove(event);
        }
    }

    void SceneMaster::handleMouseButtonDown(const MouseEvent &event) {
        Master::handleMouseButtonDown(event);
        Scene *top_stage = topScene();
        if (top_stage) {
            top_stage->handleMouseButtonDown(event);
        }
    }

    void SceneMaster::handleMouseButtonUp(const MouseEvent &event) {
        Master::handleMouseButtonUp(event);
        Scene *top_stage = topScene();
        if (top_stage) {
            top_stage->handleMouseButtonUp(event);
        }
    }

    void SceneMaster::handleMouseButtonClick(const MouseEvent &event) {
        Master::handleMouseButtonClick(event);
        Scene *top_stage = topScene();
        if (top_stage) {
            top_stage->handleMouseButtonClick(event);
        }
    }

    void SceneMaster::handleMouseButtonDoubleClick(const MouseEvent &event) {
        Master::handleMouseButtonDoubleClick(event);
        Scene *top_stage = topScene();
        if (top_stage) {
            top_stage->handleMouseButtonDoubleClick(event);
        }
    }

    void SceneMaster::handleMouseWheelScroll(const MouseEvent &event) {
        Master::handleMouseWheelScroll(event);
        Scene *top_stage = topScene();
        if (top_stage) {
            top_stage->handleMouseWheelScroll(event);
        }
    }

    void SceneMaster::handleWindowMotion(const WindowEvent &event) {
        Master::handleWindowMotion(event);
        Scene *top_stage = topScene();
        if (top_stage) {
            top_stage->handleWindowMotion(event);
        }
    }

    void SceneMaster::handleQuit() {
        Master::handleQuit();
        Scene *top_stage = topScene();
        if (top_stage) {
            top_stage->handleQuit();
        }
    }
}