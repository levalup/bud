//
// Created by kier on 11/20/15.
//

#ifndef BUD_TILE_H
#define BUD_TILE_H

#include "Node.h"
#include "Renderer.h"
#include "Point.h"
#include "Rect.h"

namespace bud {

    class Tile : public Node {
    public:
        // 按照贴图的方式绘制
        Tile();

        Tile(Texture *bud_texture);

        Tile(Texture *bud_texture, int x, int y);

        Tile(Texture *bud_texture, const Point<int> pos);

        Tile(Texture *bud_texture, const Rect &clip);

        Tile(Texture *bud_texture, const Point<int> pos, const Rect &clip);

        virtual void render() override;

        Renderer *getRenderer();

        const Rect rect() const;

        Texture *texture();

        Texture *setTexture(Texture *texture);

        Texture *updateTexture(Texture *texture);

        Point<int> pos = {0, 0};
        Rect clip = {0, 0, 0, 0};
        // FLIP flip = FLIP::NONE;  // 暂时不考虑翻转
    private:
        Texture *m_texture;
    };

}


#endif //BUD_TILE_H
