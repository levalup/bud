//
// Created by kier on 11/20/15.
//

#ifndef BUD_SPRITE_H
#define BUD_SPRITE_H

#include "Node.h"
#include "Motion.h"
#include "Point.h"
#include "Renderer.h"
#include "Rect.h"

namespace bud {

    class Sprite : public Node {
    public:
        friend class Motion;

        Sprite();

        Sprite(Texture *bud_texture);

        virtual ~Sprite();

        virtual void update() override;

        virtual void render() override;

        Renderer *getRenderer();

        // 这里返回的是最终绘制的区域（旋转之前）
        const Rect rect() const;

        // 返回精灵要绘制的贴图
        Texture *texture();

        // 设置贴图，这里不会修改绘制参数
        Texture *setTexture(Texture *texture);

        // 更新贴图，这里会重置绘图参数
        Texture *updateTexture(Texture *texture);

        // motion根节点，此类的所有finish相关操作无效，包括finishKill行为，此类只适合做动作入口
        Motion motion;

        Point<int> pos = {0, 0};            // 精灵显示的位置
        Point<double> center = {0.5, 0.5};  // 中心点，这里默认的是比例，例如[0.5, 0.5]就表示中心点
        Rect clip = {0, 0, 0, 0};           // 对于原始贴图的剪切位置
        Point<double> scale = {1, 1};       // 最终的纵横显示比例，默认[1, 1]
        double angle = 0;                   // 旋转角度
        FLIP flip;
    private:
        Texture *m_texture;
    };

}


#endif //BUD_SPRITE_H
