//
// Created by kier on 11/20/15.
//

#include "Sprite.h"
#include "Texture.h"

namespace bud {

    Sprite::Sprite()
            : Sprite(nullptr) {
    }

    Sprite::Sprite(Texture *bud_texture) {
        this->updateTexture(bud_texture);
    }

    Sprite::~Sprite() {
        // 显式调用，保证其动作的资源被释放掉
        this->motion.clear();
    }

    void Sprite::update() {
        // Node::update();  // 父节点没有行为，可以不调用
        motion.update(this);
    }

    void Sprite::render() {
        // Node::render();  // 父节点没有行为，可以不调用
        if (m_texture == nullptr) return;
        Rect dest_size = clip.base() * scale;
        m_texture->getRenderer()->copyEx(m_texture, clip, dest_size + pos, angle, dest_size.size() * center, flip);
    }

    Renderer *Sprite::getRenderer() {
        return m_texture ? m_texture->getRenderer() : nullptr;
    }

    const Rect Sprite::rect() const {
        return pos + clip.base() * scale;
    }

    Texture *Sprite::texture() {
        return this->m_texture;
    }

    Texture *Sprite::setTexture(Texture *texture) {
        Texture *old_texture = m_texture;
        m_texture = texture;
        return old_texture;
    }

    Texture *Sprite::updateTexture(Texture *texture) {
        Texture *old_texture = m_texture;
        m_texture = texture;

        if (m_texture != nullptr) {
            clip = m_texture->rect();
        }
        else {
            clip.set(0, 0, 0, 0);
        }
        pos.set(0, 0);
        center.set(0.5, 0.5);
        scale.set(1, 1);
        angle = 0;
        flip = FLIP::NONE;

        return old_texture;
    }
}
