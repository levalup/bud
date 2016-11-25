//
// Created by kier on 11/21/15.
//

#include "LocalNode.h"

namespace bud {

    void LocalNode::whenUpdate(const LocalNode::UpdateHandler &handler) {
        this->m_update_hanlder = handler;
    }

    void LocalNode::whenRender(const LocalNode::RenderHandler &handler) {
        this->m_render_hanlder = handler;
    }

    void LocalNode::update() {
        Node::update();
        if (m_update_hanlder) m_update_hanlder();
    }

    void LocalNode::render() {
        Node::render();
        if (m_render_hanlder) m_render_hanlder();
    }
}
