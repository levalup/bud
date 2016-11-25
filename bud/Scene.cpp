//
// Created by kier on 11/19/15.
//

#include "Scene.h"

#include "Renderer.h"

namespace bud {

    Scene::Scene(Renderer *bud_renderer)
            : m_bud_renderer(bud_renderer) {
    }

    Scene::~Scene() {
    }

    unsigned int Scene::updateTimes() {
        return this->m_update_times;
    }

    void Scene::handleUpdate() {
        NodeLayeredContainer::handleUpdate();
        this->m_update_times++;
    }

    void Scene::onLoad() {
    }

    void Scene::onShow() {
    }

    void Scene::onHide() {
    }

    void Scene::onExit() {
    }

    void Scene::handleLoad() {
        this->m_update_times = 0;
        this->onLoad();
    }

    void Scene::handleShow() {
        this->m_backable = false;
        this->onShow();
    }

    void Scene::handleHide() {
        this->onHide();
    }

    void Scene::handleExit() {
        this->onExit();
    }

    Renderer *Scene::getRenderer() {
        return this->m_bud_renderer;
    }


    bool Scene::backable() {
        return this->m_backable;
    }

    void Scene::back() {
        this->m_backable = true;
    }
}