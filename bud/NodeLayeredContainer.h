//
// Created by kier on 15-11-17.
//

#ifndef BUD_NODELAYEREDCONTAINER_H
#define BUD_NODELAYEREDCONTAINER_H

#include <list>
#include <vector>
#include "Node.h"

namespace bud {

    class NodeLayeredContainer : public Node {
    public:
        virtual ~NodeLayeredContainer();

        virtual void handleUpdate() override;

        virtual void handleRender() override;

        unsigned long ensureLayerSize(unsigned long n);

        unsigned long layerSize();

        // 尽量避免在同一层容器内对节点进行增删操作，同时不要在层内修改层数
        void addNode(Node *node, unsigned long n = 0);

        // 尽量避免在同一层容器内对节点进行增删操作，同时不要在层内修改层数
        void removeNode(Node *node);

        // 尽量避免在同一层容器内对节点进行增删操作，同时不要在层内修改层数
        void removeNode(Node *node, unsigned long n);

        void clearNode();

        void clearNode(unsigned long n);

        void setPreorderBaseNode(bool toggle);

        unsigned long countChildNode();

    protected:
        bool m_preorder_base_node = true;

    private:
        void updateChildNode();

        void renderChildNode();

        std::vector<std::list<Node *>> m_child_node_vector_list;

    };

}


#endif //BUD_NODELAYEREDCONTAINER_H
