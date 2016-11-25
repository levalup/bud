//
// Created by kier on 11/21/15.
//

#ifndef BUD_LOCALNODE_H
#define BUD_LOCALNODE_H

#include "Node.h"
#include <functional>

namespace bud {

    class LocalNode : public Node {
    public:
        using UpdateHandler = std::function<void()>;
        using RenderHandler = std::function<void()>;

        void whenUpdate(const UpdateHandler &handler);

        void whenRender(const RenderHandler &handler);

        virtual void update() override;

        virtual void render() override;

    private:
        UpdateHandler m_update_hanlder = nullptr;
        RenderHandler m_render_hanlder = nullptr;
    };

}


#endif //BUD_LOCALNODE_H
