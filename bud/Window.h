//
// Created by kier on 15-11-18.
//

#ifndef BUD_WINDOW_H
#define BUD_WINDOW_H

#include <string>
#include <SDL2/SDL.h>

namespace bud {
    class Renderer;

    class Rect;

    /** \enum   窗体显示模式
     * \note    C++11新特性，enum class类型
     */
    enum class WINDOW_MODE {
        WINDOWED,           /**< 窗口模式 */
        FULLSCREEN,         /**< 全屏模式 */
        FULLSCREEN_DESKTOP  /**< 桌面全屏模式 */
    };

    /** \class  Window
     * \brief   基本窗体类
     * 主要封装了SDL2的窗体相关操作
     */
    class Window {
    public:
        /**
         * \brief       建立"Untitled"标题，宽640，高480，未指定显示位置的窗体
         */
        Window();

        /**
         * \brief       建立title标题，宽640，高480，未指定显示位置的窗体
         * \param title 窗体的标题
         */
        Window(const std::string &title);

        /**
         * \brief       建立title标题，宽w，高h，未指定显示位置的窗体
         * \param title 窗体的标题
         * \param w     窗体的宽度
         * \param h     窗体的高度
         */
        Window(const std::string &title, int w, int h);

        /**
         * \brief       建立title标题，宽w，高h，未指定显示位置的窗体，传入flags为SDL参数类型
         * \param title 窗体的标题
         * \param w     窗体的宽度
         * \param h     窗体的高度
         * \param flags 窗体的标记，默认传入SDL_WINDOW_SHOWN表示直接显示窗体，详情请参考SDL2窗体相关文档
         * \note        flags在此版本中与SDL_CreateWindow中的flags保持一致
         */
        Window(const std::string &title, int w, int h, unsigned int flags);


        /**
         * \brief       建立title标题，宽w，高h，显示在[x, y]的窗体，传入flags为SDL参数类型
         * \param title 窗体的标题
         * \param x     窗体的位置的横坐标
         * \param y     窗体的位置的纵坐标
         * \param w     窗体的宽度
         * \param h     窗体的高度
         * \param flags 窗体的标记，默认传入SDL_WINDOW_SHOWN表示直接显示窗体，详情请参考SDL2窗体相关文档
         * \sa Window(const std::string &title, int w, int h, unsigned int flags)
         */
        Window(const std::string &title, int x, int y, int w, int h, unsigned int flags);

        virtual ~Window();

        /**
         * \brief   移动构造函数
         * \sa      GetFromID()
         * \note    右值引用构造仍在实验阶段，不推荐使用，（配合Window::Get方法隐式使用）
         */
        Window(Window &&borrow_window);

        Window(const Window &other) = delete;

        Window &operator=(const Window &other) = delete;

        /**
         * \brief   获取窗口维护的源数据（SDL2数据格式）
         * \return  SDL_Window类型，请参考SDL2文档
         * \note    该函数作为引擎内部操作保留，在不清楚其工作之前，请不要轻易使用
         */
        SDL_Window *meta_window();

        /**
         * \brief   返回该窗体资源是否有效
         * \return  如果窗体资源有效则返回true，否则返回false
         */
        bool valid() const;

        /**
         * \brief   获取窗体绘制的渲染器
         * \return  窗体现在使用的渲染器指针
         * \sa newRenderer()
         * 当第一次调用该方法的时候，会采用默认参数隐式调用newRenderer方法
         */
        Renderer *getRenderer();

        /**
         * \brief   新建窗体绘制渲染器
         * \param flags 渲染器构造参数，具体请参考SDL_Renderer文档
         * \param index 渲染器构造参数，具体请参考SDL_Renderer文档
         * \return  新的渲染器指针
         * \sa newRenderer()
         * \note    该函数作为引擎内部操作保留，在不清楚其工作之前，请不要轻易使用
         */
        Renderer *newRenderer(unsigned int flags, int index = -1);

        /**
         * \brief       设置窗体标题
         * \param title 新的窗体标题
         */
        void setTitle(const std::string &title);

        /**
         * \brief       设置窗体显示模式
         * \param flag  新的窗体显示的模式
         * \sa          WINDOW_MODE
         */
        void setFullscreen(WINDOW_MODE flag);

        /**
         * \brief   显示窗体
         * \sa      hide()
         */
        void show();

        /**
         * \brief   隐藏窗体
         * \sa      show()
         */
        void hide();

        /**
         * \brief           设置鼠标是否显示
         * \param toggle    该参数为true表示显示鼠标，false表示隐藏鼠标
         */
        void showCursor(bool toggle);

        /**
         * \brief           设置是否捕捉鼠标
         * \param toggle    该参数为true表示捕捉鼠标，false表示不捕捉鼠标
         * \note            SDL2.0.4以上才有相关功能，因此此函数在本版本中不可用
         */
        void captureMouse(bool toggle) = delete;

        /**
         * \brief       设置程序的图标
         * \param path  图标文件的路径，图标的格式需要是SDL_image支持的类型，因此需要在BUD函数中启动对应的模块
         * \sa          BUD
         */
        void setIcon(const std::string &path);

        /**
         * \brief   获得窗体当前的标题
         * \return  窗体当前的标题
         */
        const std::string title();

        /**
         * \brief   获得窗体当前的宽度
         * \return  窗体当前的宽度
         */
        int width();

        /**
         * \brief   获得窗体当前的高度
         * \return  窗体当前的高度
         */
        int height();

        /**
         * \brief   获得窗体当前的位置
         * \return  窗体当前的位置
         */
        const Rect rect();

        /**
         * \brief   获得当前窗体鼠标是否显示
         * \return  如果显示鼠标则返回true，否则返回false
         */
        bool cursor();

        /**
         * \brief   获得当前窗体鼠标是否捕捉
         * \return  如果捕捉鼠标则返回true，否则返回false
         * \note    SDL2.0.4以上才有相关功能，因此此函数在本版本中不可用
         */
        bool capture() = delete;

        /**
         * \brief   获得当前窗体的ID
         * \return  当前窗体的ID
         * \sa      GetFromID()
         * \sa      Event
         */
        unsigned int id();

        /**
         * \brief   根据窗体ID返回对应操作窗体的对象
         * \return  窗体的右值引用
         * \sa      Window(Window &&borrow_window)
         * \note    这个函数仍然在实验阶段，不推荐使用，返回的对象只在其id指向的窗体有效期间有效
         */
        static Window GetFromID(unsigned int window_id);

        /**
         * \brief   获得拥有当前鼠标焦点的窗体
         * \return  窗体的右值引用
         * \sa      Window(Window &&borrow_window)
         */
        static Window GetMouseFocus();

    protected:
        /**
         * \brief               构造一个操作SDL窗体数据的bud数据对象
         * \param sdl_window    需要操作的SDL窗体对象
         * \note                小心使用该方法，本类不会对这里传入的sdl_window做维护，如果这个资源在类外被释放将引发不可预知的错误，
         *                      请保证该指针在本类行为期间的有效性
         */
        explicit Window(SDL_Window *sdl_window);

    private:
        // 表示当前的数据是否是借来的，是否需要自己释放
        bool m_borrow;
        // 封装的SDL对象
        SDL_Window *m_window = nullptr;
        // 保存临时的渲染器，在析构函数中需要释放
        Renderer *m_bud_renderer = nullptr;
    };

}


#endif //BUD_WINDOW_H
