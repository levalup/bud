//
// Created by kier on 15-11-17.
//

#include "NodeLayeredContainer.h"

namespace bud {

    NodeLayeredContainer::~NodeLayeredContainer() {
        this->clearNode();
    }

    void NodeLayeredContainer::handleUpdate() {
        if (!isActived()) return;
        if (m_preorder_base_node) {
            Node::handleUpdate();
            this->updateChildNode();
        }
        else {
            this->updateChildNode();
            Node::handleUpdate();
        }
    }

    void NodeLayeredContainer::handleRender() {
        if (!isShown()) return;
        if (m_preorder_base_node) {
            Node::handleRender();
            this->renderChildNode();
        }
        else {
            this->renderChildNode();
            Node::handleRender();
        }
    }

    unsigned long NodeLayeredContainer::ensureLayerSize(unsigned long n) {
        if (this->m_child_node_vector_list.size() < n)
            this->m_child_node_vector_list.resize(n);
        return this->m_child_node_vector_list.size();
    }

    unsigned long NodeLayeredContainer::layerSize() {
        return this->m_child_node_vector_list.size();
    }

    void NodeLayeredContainer::addNode(Node *node, unsigned long n) {
        // 如果层数不保证的话，就向最后的层插入
        unsigned long max_n = this->m_child_node_vector_list.size();
        if (max_n == 0) {
            this->m_child_node_vector_list.resize(n + 1);
        } else {
            n = n < max_n ? n : max_n;
        }
        this->m_child_node_vector_list[n].push_back(node);
    }

    void NodeLayeredContainer::removeNode(Node *node) {
        for (auto &node_set : this->m_child_node_vector_list)
            node_set.remove(node);
    }

    void NodeLayeredContainer::removeNode(Node *node, unsigned long n) {
        this->m_child_node_vector_list[n].remove(node);
    }

    void NodeLayeredContainer::clearNode() {
        for (auto &node_set : this->m_child_node_vector_list) {
            for (Node *node : node_set) {
                if (node->deadHandler) {
                    auto handler = node->deadHandler;
                    handler(node);
                }
            }
            node_set.clear();
        }
    }

    void NodeLayeredContainer::clearNode(unsigned long n) {
        auto &node_set = this->m_child_node_vector_list[n];
        for (Node *node : node_set) {
            if (node->deadHandler) {
                auto handler = node->deadHandler;
                handler(node);
            }
        }
        node_set.clear();
    }

    void NodeLayeredContainer::setPreorderBaseNode(bool toggle) {
        this->m_preorder_base_node = toggle;
    }

    void NodeLayeredContainer::updateChildNode() {
        for (auto &node_set : this->m_child_node_vector_list) {
            for (auto it = node_set.begin(); it != node_set.end();) {
                Node *node = *it;
                node->handleUpdate();
                if (node->dead()) {
                    it = node_set.erase(it);
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
    }

    void NodeLayeredContainer::renderChildNode() {
        for (auto &node_set : this->m_child_node_vector_list)
            for (Node *node : node_set)
                node->handleRender();
    }

    unsigned long NodeLayeredContainer::countChildNode() {
        unsigned long count = 0;
        for (auto &node_set : this->m_child_node_vector_list)
            count += node_set.size();
        return count;
    }
}