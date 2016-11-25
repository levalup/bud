//
// Created by kier on 15-11-18.
//

#include "Font.h"
#include "Notifier.h"

using namespace std;

namespace bud {
    Font::Font()
            : Font(nullptr) {
    }

    Font::Font(TTF_Font *font)
            : m_font(font), m_font_size(0) {
    }

    Font::Font(const std::string &path, int ptsize)
            : m_font(nullptr), m_font_size(0) {
        load(path, ptsize);
    }

    Font::~Font() {
        dispose();
    }

    TTF_Font *Font::meta_font() {
        return m_font;
    }

    bool Font::valid() const {
        return m_font != nullptr;
    }

    void Font::dispose() {
        if (m_font != nullptr) {
            TTF_CloseFont(m_font);
            m_font = nullptr;
        }
    }

    bool Font::hasDisposed() const {
        return m_font == nullptr;
    }

    bool Font::load(const std::string &path, int ptsize) {
        dispose();
        m_font = raw_open_font(path, ptsize);
        m_font_size = ptsize;
        return m_font != nullptr;
    }

    int Font::font_size() {
        return m_font_size;
    }

    TTF_Font *Font::raw_open_font(const std::string &path, int ptsize) {
        TTF_Font *newFont = TTF_OpenFont(path.c_str(), ptsize);
        if (newFont == nullptr) {
            Notifier::err(string("Error: load font \"") + path.c_str() + "\" error: " + TTF_GetError());
        }
        return newFont;
    }
}
