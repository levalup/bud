//
// Created by kier on 15-11-18.
//

#include "Renderer.h"

#include "Color.h"
#include "Point.h"
#include "Rect.h"
#include "Texture.h"

namespace bud {
    Renderer::Renderer()
            : Renderer(nullptr) {
        //ctor
    }

    Renderer::Renderer(SDL_Renderer *renderer)
            : m_renderer(renderer), m_bud_texture(nullptr) {

    }

    Renderer::~Renderer() {
        //dtor
        this->dispose();
    }

    SDL_Renderer *Renderer::meta_renderer() {
        return m_renderer;
    }

    bool Renderer::valid() const {
        return m_renderer != nullptr;
    }

    void Renderer::dispose() {
        if (m_renderer != nullptr) {
            SDL_DestroyRenderer(m_renderer);
            m_renderer = nullptr;
        }
    }

    bool Renderer::hasDisposed() const {
        return m_renderer == nullptr;
    }

    void Renderer::render() {
        SDL_RenderPresent(m_renderer);
    }

    Texture *Renderer::setTarget(Texture *texture) {
        if (texture == nullptr)
            return setTargetDefault();

        Texture *old_bud_texture = m_bud_texture;
        m_bud_texture = texture;
        SDL_SetRenderTarget(m_renderer, m_bud_texture->meta_texture());
        return old_bud_texture;
    }

    Texture *Renderer::setTargetDefault() {
        Texture *old_bud_texture = m_bud_texture;
        m_bud_texture = nullptr;
        SDL_SetRenderTarget(m_renderer, nullptr);
        return old_bud_texture;
    }

    Texture *Renderer::target() {
        return m_bud_texture;
    }

    void Renderer::setDrawColor(byte r, byte g, byte b, byte a) {
        SDL_SetRenderDrawColor(m_renderer, r, g, b, a);
    }

    void Renderer::setDrawColor(const Color &color) {
        setDrawColor(color.r, color.g, color.b, color.a);
    }

    const Color Renderer::drawColor() {
        Uint8 r, g, b, a;
        SDL_GetRenderDrawColor(m_renderer, &r, &g, &b, &a);
        return Color(r, g, b, a);
    }

    void Renderer::clear() {
        SDL_RenderClear(m_renderer);
    }

    void Renderer::clear(byte r, byte g, byte b, byte a) {
        this->setDrawColor(r, g, b, a);
        this->clear();
    }

    void Renderer::clear(const Color &color) {
        clear(color.r, color.g, color.b, color.a);
    }

    void Renderer::copy(Texture *texture) {
        SDL_RenderCopy(m_renderer, texture->meta_texture(), nullptr, nullptr);
    }

    void Renderer::copy(Texture *texture, int x, int y) {
        SDL_Rect dst = {x, y, texture->width(), texture->height()};
        SDL_RenderCopy(m_renderer, texture->meta_texture(), nullptr, &dst);
    }

    void Renderer::copy(Texture *texture, const Point<int> &dest) {
        SDL_Rect dst = {dest.x, dest.y, texture->width(), texture->height()};
        SDL_RenderCopy(m_renderer, texture->meta_texture(), nullptr, &dst);
    }

    void Renderer::copy(Texture *texture, const Rect &dest) {
        SDL_Rect dst = dest.meta_rect();
        SDL_RenderCopy(m_renderer, texture->meta_texture(), nullptr, &dst);
    }

    void Renderer::copy(Texture *texture, const Rect &src, const Rect &dest) {
        SDL_Rect sc = src.meta_rect();
        SDL_Rect dst = dest.meta_rect();
        SDL_RenderCopy(m_renderer, texture->meta_texture(), &sc, &dst);
    }

    void Renderer::copyEx(Texture *texture, const Rect &srcrect, const Rect &dstrect, double angle,
                          const Point<int> &center, bool flip_H, bool flip_V) {
        SDL_Rect src = srcrect.meta_rect();
        SDL_Rect dst = dstrect.meta_rect();
        SDL_Point ctr = center.meta_point();
        SDL_RendererFlip flip = SDL_FLIP_NONE;
        if (flip_H) {
            flip = (SDL_RendererFlip) (flip | SDL_FLIP_HORIZONTAL);
        }
        if (flip_V) {
            flip = (SDL_RendererFlip) (flip | SDL_FLIP_VERTICAL);
        }
        SDL_RenderCopyEx(m_renderer, texture->meta_texture(), &src, &dst, angle, &ctr, flip);
    }

    void Renderer::copyEx(Texture *texture, const Rect &srcrect, const Rect &dstrect, double angle,
                          const Point<int> &center, FLIP flip_flag) {
        SDL_Rect src = srcrect.meta_rect();
        SDL_Rect dst = dstrect.meta_rect();
        SDL_Point ctr = center.meta_point();
        SDL_RendererFlip flip = SDL_FLIP_NONE;
        switch (flip_flag) {
            case FLIP::NONE:
                flip = SDL_FLIP_NONE;
                break;
            case FLIP::H:
                flip = SDL_FLIP_HORIZONTAL;
                break;
            case FLIP::V:
                flip = SDL_FLIP_VERTICAL;
                break;
            case FLIP::H_V:
                flip = (SDL_RendererFlip) (SDL_FLIP_HORIZONTAL | SDL_FLIP_VERTICAL);
                break;
        }
        SDL_RenderCopyEx(m_renderer, texture->meta_texture(), &src, &dst, angle, &ctr, flip);
    }

    void Renderer::line(const Point<int> &p1, const Point<int> &p2) {
        SDL_RenderDrawLine(m_renderer, p1.x, p1.y, p2.x, p2.y);
    }

    void Renderer::line(const std::list<Point<int>> &ps) {
        SDL_Point *points = new SDL_Point[ps.size()];
        int count = 0;
        for (std::list<Point<int>>::const_iterator it = ps.begin(); it != ps.end(); ++it) {
            it->raw_fill(points + (count++));
        }
        SDL_RenderDrawLines(m_renderer, points, count);
        delete[] points;
    }

    void Renderer::line(const std::list<Point<int>> &ps, const Point<int> &base) {
        SDL_Point *points = new SDL_Point[ps.size()];
        int count = 0;
        for (std::list<Point<int>>::const_iterator it = ps.begin(); it != ps.end(); ++it) {
            (*it + base).raw_fill(points + (count++));
        }
        SDL_RenderDrawLines(m_renderer, points, count);
        delete[] points;
    }

    void Renderer::point(const Point<int> &p) {
        SDL_RenderDrawPoint(m_renderer, p.x, p.y);
    }

    void Renderer::point(const std::list<Point<int>> &ps) {
        SDL_Point *points = new SDL_Point[ps.size()];
        int count = 0;
        for (std::list<Point<int>>::const_iterator it = ps.begin(); it != ps.end(); ++it) {
            it->raw_fill(points + (count++));
        }
        SDL_RenderDrawPoints(m_renderer, points, count);
        delete[] points;
    }

    void Renderer::point(const std::list<Point<int>> &ps, const Point<int> &base) {
        SDL_Point *points = new SDL_Point[ps.size()];
        int count = 0;
        for (std::list<Point<int>>::const_iterator it = ps.begin(); it != ps.end(); ++it) {
            (*it + base).raw_fill(points + (count++));
        }
        SDL_RenderDrawPoints(m_renderer, points, count);
        delete[] points;
    }

    void Renderer::rect(const Rect &r) {
        SDL_Rect rect = r.meta_rect();
        SDL_RenderDrawRect(m_renderer, &rect);
    }

    void Renderer::rect(const std::list<Rect> &rs) {
        SDL_Rect *rects = new SDL_Rect[rs.size()];
        int count = 0;
        for (std::list<Rect>::const_iterator it = rs.begin(); it != rs.end(); ++it) {
            it->raw_fill(rects + (count++));
        }
        SDL_RenderDrawRects(m_renderer, rects, count);
        delete[] rects;
    }

    void Renderer::rect(const std::list<Rect> &rs, const Point<int> &base) {
        SDL_Rect *rects = new SDL_Rect[rs.size()];
        int count = 0;
        for (std::list<Rect>::const_iterator it = rs.begin(); it != rs.end(); ++it) {
            (*it + base).raw_fill(rects + (count++));
        }
        SDL_RenderDrawRects(m_renderer, rects, count);
        delete[] rects;
    }

    void Renderer::fill(const Rect &r) {
        SDL_Rect rect = r.meta_rect();
        SDL_RenderFillRect(m_renderer, &rect);
    }

    void Renderer::fill(const std::list<Rect> &rs) {
        SDL_Rect *rects = new SDL_Rect[rs.size()];
        int count = 0;
        for (std::list<Rect>::const_iterator it = rs.begin(); it != rs.end(); ++it) {
            it->raw_fill(rects + (count++));
        }
        SDL_RenderFillRects(m_renderer, rects, count);
        delete[] rects;
    }

    void Renderer::fill(const std::list<Rect> &rs, const Point<int> &base) {
        SDL_Rect *rects = new SDL_Rect[rs.size()];
        int count = 0;
        for (std::list<Rect>::const_iterator it = rs.begin(); it != rs.end(); ++it) {
            (*it + base).raw_fill(rects + (count++));
        }
        SDL_RenderFillRects(m_renderer, rects, count);
        delete[] rects;
    }

    void Renderer::text(const std::string &str, Font *font, int x, int y) {
        //Uint8 r, g, b, a;
        //SDL_GetRenderDrawColor(m_renderer, &r, &g, &b, &a);
        //text(str, font, x, y, r, g, b);
        //text(str, font, x, y, drawColor());
        Texture texture(this, font, str);
        this->copy(&texture, x, y);
    }

    void Renderer::text(const std::string &str, Font *font, int x, int y, byte r, byte g, byte b) {
        Texture texture(this, font, str, r, g, b);
        this->copy(&texture, x, y);
    }

    void Renderer::text(const std::string &str, Font *font, int x, int y, const Color &color) {
        Texture texture(this, font, str, color);
        this->copy(&texture, x, y);
    }
}