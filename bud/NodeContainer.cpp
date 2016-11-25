//
// Created by kier on 15-11-17.
//

#include "NodeContainer.h"

namespace bud {

    NodeContainer::~NodeContainer() {
        this->clearNode();
    }

    void NodeContainer::handleUpdate() {
        if (!isActived()) return;
        if (this->m_preorder_base_node) {
            Node::handleUpdate();
            this->updateChildNode();
        }
        else {
            this->updateChildNode();
            Node::handleUpdate();
        }
    }

    void NodeContainer::handleRender() {
        if (!isShown()) return;
        if (this->m_preorder_base_node) {
            Node::handleRender();
            this->renderChildNode();
        }
        else {
            this->renderChildNode();
            Node::handleRender();
        }
    }

    void NodeContainer::addNode(Node *node) {
        this->m_child_node_list.push_back(node);
    }

    void NodeContainer::removeNode(Node *node) {
        this->m_child_node_list.remove(node);
    }

    void NodeContainer::clearNode() {
        for (Node *node : this->m_child_node_list) {
            if (node->deadHandler) {
                auto handler = node->deadHandler;
                handler(node);
            }
        }
        this->m_child_node_list.clear();
    }

    void NodeContainer::setPreorderBaseNode(bool toggle) {
        this->m_preorder_base_node = toggle;
    }

    void NodeContainer::updateChildNode() {
        for (auto it = this->m_child_node_list.begin(); it != this->m_child_node_list.end();) {
            Node *node = *it;
            node->handleUpdate();
            if (node->dead()) {
                it = m_child_node_list.erase(it);
                if (node->deadHandler) {
                    auto handler = node->deadHandler;
                    handler(node);
                }
            }
            else {
                ++it;
            }
        }
    }

    void NodeContainer::renderChildNode() {
        for (Node *node : this->m_child_node_list)
            node->handleRender();
    }

    unsigned long NodeContainer::countChildNode() {
        return this->m_child_node_list.size();
    }
}
