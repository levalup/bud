//
// Created by kier on 15-11-17.
//

#ifndef BUD_NODECONTAINER_H
#define BUD_NODECONTAINER_H

#include "Node.h"

#include <unordered_set>
#include <list>

namespace bud {

    class NodeContainer : public Node {
    public:
        virtual ~NodeContainer();

        virtual void handleUpdate() override;

        virtual void handleRender() override;

        // 尽量避免在同一层容器内对节点进行增删操作
        void addNode(Node *node);

        // 尽量避免在同一层容器内对节点进行增删操作
        void removeNode(Node *node);

        void clearNode();

        void setPreorderBaseNode(bool toggle);

        unsigned long countChildNode();

    protected:
        bool m_preorder_base_node = true;

    private:
        void updateChildNode();

        void renderChildNode();

        std::list<Node *> m_child_node_list;
    };

}


#endif //BUD_NODECONTAINER_H
