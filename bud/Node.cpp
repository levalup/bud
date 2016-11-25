//
// Created by kier on 15-11-17.
//

#include "Node.h"

#include <cstdlib>

namespace bud {

    Node::~Node() {
        _alloc(0);
    }

    void Node::update() {

    }

    void Node::render() {

    }

    void Node::handleUpdate() {
        if (!isActived()) return;
        this->update();
    }

    void Node::handleRender() {
        if (!isShown()) return;
        this->render();
    }

    bool Node::dead() {
        return this->m_dead;
    }

    void Node::kill() {
        this->m_dead = true;
        this->active(false);
        this->show(false);
    }

    void Node::selfDelete(bool toggle) {
        if (toggle)
            this->deadHandler = this->Deleter;
        else
            this->deadHandler = nullptr;
    }

    void Node::Deleter(Node *node) {
        delete node;
    }

    bool Node::isActived() const {
        return m_actived;
    }

    void Node::active(bool actived) {
        this->m_actived = actived;
    }

    bool Node::isShown() const {
        return m_shown;
    }

    void Node::show(bool shown) {
        this->m_shown = shown;
    }

    void Node::forceUpdate() {
        bool has_actived = this->m_actived;
        this->m_actived = true;
        this->handleUpdate();
        this->m_actived = has_actived;
    }

    void Node::forceRender() {
        bool has_shown = this->m_shown;
        this->m_shown = true;
        this->handleRender();
        this->m_shown = has_shown;
    }

    void *Node::_alloc(size_t _size) {
        if (_size == 0) {
            if (m_alloc) free(m_alloc);
            m_alloc = nullptr;
        } else if (m_alloc) {
            m_alloc = realloc(m_alloc, _size);
        } else
            m_alloc = malloc(_size);
        m_alloc_size = _size;
        return m_alloc;
    }

    void *Node::_allocated_data() {
        return m_alloc;
    }

    size_t Node::allocated_size() {
        return m_alloc_size;
    }
}
