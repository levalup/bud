//
// Created by kier on 15-11-18.
//

#ifndef BUD_BUD_H
#define BUD_BUD_H

namespace bud {

    class BUD {
    public:
        // 默认构造函数, 会调用默认初始化模块的参数
        BUD();

        // 根据模块参数初始化SDL的模块,参数表示SDL_Init的参数和IMG_Init的参数
        BUD(unsigned int base_flag, unsigned int image_flag);

        // 析构函数中处理资源释放的情况,执行各个模块的Quit操作
        virtual ~BUD();

        // 返回初始化操作是否失败
        bool failed() const;

    private:
        // 记录初始化SDL采用的参数
        unsigned int m_base_flag;
        // 记录初始化IMG采用的参数
        int m_image_flag;
        // 记录初始化是否失败的变量
        bool m_failed;
        // 此变量为真表示基本SDL模块加载成功
        bool m_base_inited;
        // 此变量为真表示image模块加载成功
        bool m_image_inited;
        // 此变量为真表示ttf模块加载成功
        bool m_ttf_inited;
        // 此变量为真表示mixer模块加载成功
        bool m_mixer_inited;
    };

}

#endif //BUD_BUD_H
