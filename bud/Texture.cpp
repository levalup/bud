//
// Created by kier on 15-11-18.
//

#include <SDL2/SDL_image.h>
#include "Color.h"
#include "Font.h"
#include "Rect.h"
#include "Renderer.h"

#include "Texture.h"
#include "Notifier.h"

namespace bud {
    Texture::Texture(Renderer *bud_renderer)
            : Texture(bud_renderer, nullptr) {
    }

    Texture::Texture(Renderer *bud_renderer, SDL_Texture *texture)
            : m_bud_renderer(bud_renderer), m_texture(texture) {
        SDL_QueryTexture(m_texture, nullptr, nullptr, &m_width, &m_height);
    }

    Texture::Texture(Renderer *bud_renderer, const std::string &path)
            : m_bud_renderer(bud_renderer), m_texture(nullptr) {
        load(path);
    }

    Texture::Texture(Renderer *bud_renderer, const std::string &path, byte r, byte g, byte b)
            : m_bud_renderer(bud_renderer), m_texture(nullptr) {
        load(path, r, b, b);
    }

    Texture::Texture(Renderer *bud_renderer, const std::string &path, const Color &color)
            : m_bud_renderer(bud_renderer), m_texture(nullptr) {
        load(path, color);
    }

    Texture::Texture(Renderer *bud_renderer, int w, int h)
            : m_bud_renderer(bud_renderer), m_texture(nullptr) {
        create(w, h);
    }

    Texture::Texture(Renderer *bud_renderer, Font *font, const std::string &text, RENDER_TTF type)
            : m_bud_renderer(bud_renderer), m_texture(nullptr) {
        load(font, text, type);
    }

    Texture::Texture(Renderer *bud_renderer, Font *font, const std::string &text, byte r, byte g, byte b,
                     RENDER_TTF type)
            : m_bud_renderer(bud_renderer), m_texture(nullptr) {
        load(font, text, r, g, b, type);
    }

    Texture::Texture(Renderer *bud_renderer, Font *font, const std::string &text, const Color &color,
                     RENDER_TTF type)
            : m_bud_renderer(bud_renderer), m_texture(nullptr) {
        load(font, text, color, type);
    }

    Texture::~Texture() {
        this->dispose();
    }

    SDL_Texture *Texture::meta_texture() {
        return m_texture;
    }

    bool Texture::valid() const {
        return m_texture != nullptr;
    }

    void Texture::dispose() {
        if (m_texture != nullptr) {
            SDL_DestroyTexture(m_texture);
            m_texture = nullptr;
        }
    }

    bool Texture::hasDisposed() const {
        return m_texture == nullptr;
    }

    bool Texture::create(int w, int h) {
        dispose();
        m_texture = raw_create_texture(w, h);
        m_width = w;
        m_height = h;
        return m_texture != nullptr;
    }

    bool Texture::load(const std::string &path) {
        dispose();
        m_texture = raw_image_load(path, SDL_FALSE, 0, 0, 0);
        SDL_QueryTexture(m_texture, nullptr, nullptr, &m_width, &m_height);
        return m_texture != nullptr;
    }

    bool Texture::load(const std::string &path, byte r, byte g, byte b) {
        dispose();
        m_texture = raw_image_load(path, SDL_TRUE, r, g, b);
        SDL_QueryTexture(m_texture, nullptr, nullptr, &m_width, &m_height);
        return m_texture != nullptr;
    }

    bool Texture::load(const std::string &path, const Color &color) {
        return load(path, color.r, color.g, color.b);
    }

    bool Texture::load(Font *font, const std::string &text, RENDER_TTF type) {
        return load(font, text, Color::Black, type);
    }

    bool Texture::load(Font *font, const std::string &text, byte r, byte g, byte b, RENDER_TTF type) {
        dispose();
        SDL_Color color = {r, g, b};
        m_texture = raw_text_texture(text, font->meta_font(), color, type);
        SDL_QueryTexture(m_texture, nullptr, nullptr, &m_width, &m_height);
        return m_texture != nullptr;
    }

    bool Texture::load(Font *font, const std::string &text, const Color &color, RENDER_TTF type) {
        return load(font, text, color.r, color.g, color.b, type);
    }

    Renderer *Texture::getRenderer() {
        return m_bud_renderer;
    }

    const Rect Texture::rect() {
        return Rect(m_width, m_height);
    }

    void Texture::setColorMod(const Color &color) {
        SDL_SetTextureColorMod(m_texture, color.r, color.g, color.b);
    }

    const Color Texture::getColorMod() {
        Uint8 r, g, b;
        SDL_GetTextureColorMod(m_texture, &r, &g, &b);
        return {r, g, b};
    }

    void Texture::setAlphaMod(byte alpha) {
        SDL_SetTextureAlphaMod(m_texture, alpha);
    }

    byte Texture::getAlphaMod() {
        Uint8 alpha;
        SDL_GetTextureAlphaMod(m_texture, &alpha);
        return alpha;
    }

    void Texture::setMod(const Color &color) {
        SDL_SetTextureColorMod(m_texture, color.r, color.g, color.b);
        SDL_SetTextureAlphaMod(m_texture, color.a);
    }

    const Color Texture::getMod() {
        Uint8 r, g, b, a;
        SDL_GetTextureColorMod(m_texture, &r, &g, &b);
        SDL_GetTextureAlphaMod(m_texture, &a);
        return {r, g, b, a};
    }

    int Texture::width() {
        return m_width;
    }

    int Texture::height() {
        return m_height;
    }

    SDL_Texture *Texture::raw_image_load(const std::string &path, int flag, Uint8 r, Uint8 g, Uint8 b) const {
        SDL_Texture *newTexture = nullptr;
        SDL_Surface *loadedSurface = IMG_Load(path.c_str());
        if (loadedSurface == nullptr) {
            Notifier::err(B("Error: Load image \"", path.c_str(), "\" error: ", IMG_GetError()));
        }
        else {
            if (flag && SDL_SetColorKey(loadedSurface, flag, SDL_MapRGB(loadedSurface->format, r, g, b)) < 0) {
                Notifier::err(B("Error: set color key \"", path.c_str(), "\" error: ", SDL_GetError()));
            }
            newTexture = SDL_CreateTextureFromSurface(m_bud_renderer->meta_renderer(), loadedSurface);
            if (newTexture == nullptr) {
                Notifier::err(B("Error: create texture \"", path.c_str(), "\" error: ", SDL_GetError()));
            }
            SDL_FreeSurface(loadedSurface);
        }
        // SDL_SetTextureBlendMode(newTexture, SDL_BLENDMODE_BLEND);
        return newTexture;
    }

    SDL_Texture *Texture::raw_create_texture(int w, int h) const {
        SDL_Texture *newTexture = nullptr;
        newTexture = SDL_CreateTexture(m_bud_renderer->meta_renderer(), SDL_PIXELFORMAT_RGBA8888,
                                       SDL_TEXTUREACCESS_TARGET, w, h);
        if (newTexture == nullptr) {
            Notifier::err(B("Error: create texture error: ", SDL_GetError()));
        }
        // SDL_SetTextureBlendMode(newTexture, SDL_BLENDMODE_BLEND);
        return newTexture;
    }

    SDL_Texture *Texture::raw_text_texture(const std::string &text, TTF_Font *font, SDL_Color fg,
                                           RENDER_TTF type) const {
        SDL_Texture *newTexture = nullptr;
        SDL_Surface *textSurface = nullptr;
        switch (type) {
            case RENDER_TTF::SOLID:
                textSurface = TTF_RenderUTF8_Solid(font, text.c_str(), fg);
                break;
            case RENDER_TTF::SHADED: {
                SDL_Color bg;
                m_bud_renderer->drawColor().raw_fill(&bg);
                textSurface = TTF_RenderUTF8_Shaded(font, text.c_str(), fg, bg);
            }
                break;
            case RENDER_TTF::BLENDED:
                textSurface = TTF_RenderUTF8_Blended(font, text.c_str(), fg);
                break;
                //case BLENDED_WRAPPED_RENDER:
                //textSurface = TTF_RenderUTF8_Blended_Wrapped(font, text.c_str(), fg, 0);
                //break;
        }
        if (textSurface == nullptr) {
            Notifier::err(B("Error: render text \"", text.c_str(), "\" error: ", TTF_GetError()));
        }
        else {
            newTexture = SDL_CreateTextureFromSurface(m_bud_renderer->meta_renderer(), textSurface);
            if (newTexture == nullptr) {
                Notifier::err(B("Error: create texture \"", text.c_str(), "\" error: ", SDL_GetError()));
            }
            SDL_FreeSurface(textSurface);
        }
        // SDL_SetTextureBlendMode(newTexture, SDL_BLENDMODE_BLEND);
        return newTexture;
    }
}