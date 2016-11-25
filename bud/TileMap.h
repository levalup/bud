//
// Created by kier on 11/20/15.
//

#ifndef BUD_TILEMAP_H
#define BUD_TILEMAP_H

#include "Node.h"
#include "Rect.h"

namespace bud {

    class Tile;
    class TileMap : public Node {
    public:
        // 相对于贴图逻辑大小的显示窗体位置，图块理论上只绘制显示的部分
        Rect viewport = {0, 0, 0, 0};
    };

}


#endif //BUD_TILEMAP_H
