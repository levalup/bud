//
// Created by kier on 11/20/15.
//

#include "Tile.h"
#include "Texture.h"

namespace bud {

    Tile::Tile()
            : m_texture(nullptr) {
    }

    Tile::Tile(Texture *bud_texture)
            : m_texture(bud_texture) {
        if (m_texture != nullptr) {
            this->clip = m_texture->rect();
        }
    }

    Tile::Tile(Texture *bud_texture, int x, int y)
            : pos(x, y), m_texture(bud_texture) {
        if (m_texture != nullptr) {
            this->clip = m_texture->rect();
        }
    }

    Tile::Tile(Texture *bud_texture, const Point<int> pos)
            : pos(pos), m_texture(bud_texture) {
        if (m_texture != nullptr) {
            this->clip = m_texture->rect();
        }
    }

    Tile::Tile(Texture *bud_texture, const Rect &clip)
            : clip(clip), m_texture(bud_texture) {
    }

    Tile::Tile(Texture *bud_texture, const Point<int> pos, const Rect &clip)
            : pos(pos), clip(clip), m_texture(bud_texture) {
    }

    void Tile::render() {
        Node::render();
        if (m_texture == nullptr) return;
        m_texture->getRenderer()->copy(m_texture, clip, pos + clip.base());
    }

    Renderer *Tile::getRenderer() {
        return m_texture ? m_texture->getRenderer() : nullptr;
    }

    const Rect Tile::rect() const {
        return pos + clip.base();
    }

    Texture *Tile::texture() {
        return this->m_texture;
    }

    Texture *Tile::setTexture(Texture *texture) {
        Texture *old_texture = m_texture;
        m_texture = texture;
        return old_texture;
    }

    Texture *Tile::updateTexture(Texture *texture) {
        Texture *old_texture = m_texture;
        m_texture = texture;

        if (m_texture != nullptr) {
            clip = m_texture->rect();
        }
        else {
            clip.set(0, 0, 0, 0);
        }
        pos.set(0, 0);

        return old_texture;
    }
}
