//
// Created by kier on 15-11-18.
//

#include "Color.h"

namespace bud {
    Color::Color()
            : r(0xFF), g(0xFF), b(0xFF), a(0xFF) {
    }

    Color::Color(unsigned int code)
            : r((byte) ((code & 0xFF0000) >> 16)), g((byte) ((code & 0xFF00) >> 8)), b((byte) (code & 0xFF)), a(0xFF) {

    }

    Color::Color(unsigned int code, byte a)
            : r((byte) ((code & 0xFF0000) >> 16)), g((byte) ((code & 0xFF00) >> 8)), b((byte) (code & 0xFF)), a(a) {

    }

    Color::Color(byte r, byte g, byte b)
            : r(r), g(g), b(b), a(0xFF) {

    }

    Color::Color(byte r, byte g, byte b, byte a)
            : r(r), g(g), b(b), a(a) {

    }

    Color::Color(const Color &other)
            : r(other.r), g(other.g), b(other.b), a(other.a) {
    }

    const Color Color::alpha(byte __a) const {
        return bud::Color(r, g, b, __a);
    }

    unsigned int Color::code() {
        return (r << 16) | (g << 8) | b;
    }

    Color &Color::operator=(const Color &other) {
        this->r = other.r;
        this->g = other.g;
        this->b = other.b;
        this->a = other.a;
        return *this;
    }

    void Color::raw_fill(SDL_Color *sdl_color) const {
        sdl_color->r = r;
        sdl_color->g = g;
        sdl_color->b = b;
        sdl_color->a = a;
    }

    const SDL_Color Color::meta_color() const {
        SDL_Color sdl_color;
        sdl_color.r = r;
        sdl_color.g = g;
        sdl_color.b = b;
        sdl_color.a = a;
        return sdl_color;
    }

    const Color Color::LightPink(0xFFB6C1);
    const Color Color::Pink(0xFFC0CB);
    const Color Color::Crimson(0xDC143C);
    const Color Color::LavenderBlush(0xFFF0F5);
    const Color Color::PaleVioletRed(0xDB7093);
    const Color Color::HotPink(0xFF69B4);
    const Color Color::DeepPink(0xFF1493);
    const Color Color::MediumVioletRed(0xC71585);
    const Color Color::Orchid(0xDA70D6);
    const Color Color::Thistle(0xD8BFD8);
    const Color Color::Plum(0xDDA0DD);
    const Color Color::Violet(0xEE82EE);
    const Color Color::Magenta(0xFF00FF);
    const Color Color::Fuchsia(0xFF00FF);
    const Color Color::DarkMagenta(0x8B008B);
    const Color Color::Purple(0x800080);
    const Color Color::MediumOrchid(0xBA55D3);
    const Color Color::DarkVoilet(0x9400D3);
    const Color Color::DarkOrchid(0x9932CC);
    const Color Color::Indigo(0x4B0082);
    const Color Color::BlueViolet(0x8A2BE2);
    const Color Color::MediumPurple(0x9370DB);
    const Color Color::MediumSlateBlue(0x7B68EE);
    const Color Color::SlateBlue(0x6A5ACD);
    const Color Color::DarkSlateBlue(0x483D8B);
    const Color Color::Lavender(0xE6E6FA);
    const Color Color::GhostWhite(0xF8F8FF);
    const Color Color::Blue(0x0000FF);
    const Color Color::MediumBlue(0x0000CD);
    const Color Color::MidnightBlue(0x191970);
    const Color Color::DarkBlue(0x00008B);
    const Color Color::Navy(0x000080);
    const Color Color::RoyalBlue(0x4169E1);
    const Color Color::CornflowerBlue(0x6495ED);
    const Color Color::LightSteelBlue(0xB0C4DE);
    const Color Color::LightSlateGray(0x778899);
    const Color Color::SlateGray(0x708090);
    const Color Color::DoderBlue(0x1E90FF);
    const Color Color::AliceBlue(0xF0F8FF);
    const Color Color::SteelBlue(0x4682B4);
    const Color Color::LightSkyBlue(0x87CEFA);
    const Color Color::SkyBlue(0x87CEEB);
    const Color Color::DeepSkyBlue(0x00BFFF);
    const Color Color::LightBLue(0xADD8E6);
    const Color Color::PowDerBlue(0xB0E0E6);
    const Color Color::CadetBlue(0x5F9EA0);
    const Color Color::Azure(0xF0FFFF);
    const Color Color::LightCyan(0xE1FFFF);
    const Color Color::PaleTurquoise(0xAFEEEE);
    const Color Color::Cyan(0x00FFFF);
    const Color Color::Aqua(0x00FFFF);
    const Color Color::DarkTurquoise(0x00CED1);
    const Color Color::DarkSlateGray(0x2F4F4F);
    const Color Color::DarkCyan(0x008B8B);
    const Color Color::Teal(0x008080);
    const Color Color::MediumTurquoise(0x48D1CC);
    const Color Color::LightSeaGreen(0x20B2AA);
    const Color Color::Turquoise(0x40E0D0);
    const Color Color::Auqamarin(0x7FFFAA);
    const Color Color::MediumAquamarine(0x00FA9A);
    const Color Color::MediumSpringGreen(0xF5FFFA);
    const Color Color::MintCream(0x00FF7F);
    const Color Color::SpringGreen(0x3CB371);
    const Color Color::SeaGreen(0x2E8B57);
    const Color Color::Honeydew(0xF0FFF0);
    const Color Color::LightGreen(0x90EE90);
    const Color Color::PaleGreen(0x98FB98);
    const Color Color::DarkSeaGreen(0x8FBC8F);
    const Color Color::LimeGreen(0x32CD32);
    const Color Color::Lime(0x00FF00);
    const Color Color::ForestGreen(0x228B22);
    const Color Color::Green(0x008000);
    const Color Color::DarkGreen(0x006400);
    const Color Color::Chartreuse(0x7FFF00);
    const Color Color::LawnGreen(0x7CFC00);
    const Color Color::GreenYellow(0xADFF2F);
    const Color Color::OliveDrab(0x556B2F);
    const Color Color::Beige(0x6B8E23);
    const Color Color::LightGoldenrodYellow(0xFAFAD2);
    const Color Color::Ivory(0xFFFFF0);
    const Color Color::LightYellow(0xFFFFE0);
    const Color Color::Yellow(0xFFFF00);
    const Color Color::Olive(0x808000);
    const Color Color::DarkKhaki(0xBDB76B);
    const Color Color::LemonChiffon(0xFFFACD);
    const Color Color::PaleGodenrod(0xEEE8AA);
    const Color Color::Khaki(0xF0E68C);
    const Color Color::Gold(0xFFD700);
    const Color Color::Cornislk(0xFFF8DC);
    const Color Color::GoldEnrod(0xDAA520);
    const Color Color::FloralWhite(0xFFFAF0);
    const Color Color::OldLace(0xFDF5E6);
    const Color Color::Wheat(0xF5DEB3);
    const Color Color::Moccasin(0xFFE4B5);
    const Color Color::Orange(0xFFA500);
    const Color Color::PapayaWhip(0xFFEFD5);
    const Color Color::BlanchedAlmond(0xFFEBCD);
    const Color Color::NavajoWhite(0xFFDEAD);
    const Color Color::AntiqueWhite(0xFAEBD7);
    const Color Color::Tan(0xD2B48C);
    const Color Color::BrulyWood(0xDEB887);
    const Color Color::Bisque(0xFFE4C4);
    const Color Color::DarkOrange(0xFF8C00);
    const Color Color::Linen(0xFAF0E6);
    const Color Color::Peru(0xCD853F);
    const Color Color::PeachPuff(0xFFDAB9);
    const Color Color::SandyBrown(0xF4A460);
    const Color Color::Chocolate(0xD2691E);
    const Color Color::SaddleBrown(0x8B4513);
    const Color Color::SeaShell(0xFFF5EE);
    const Color Color::Sienna(0xA0522D);
    const Color Color::LightSalmon(0xFFA07A);
    const Color Color::Coral(0xFF7F50);
    const Color Color::OrangeRed(0xFF4500);
    const Color Color::DarkSalmon(0xE9967A);
    const Color Color::Tomato(0xFF6347);
    const Color Color::MistyRose(0xFFE4E1);
    const Color Color::Salmon(0xFA8072);
    const Color Color::Snow(0xFFFAFA);
    const Color Color::LightCoral(0xF08080);
    const Color Color::RosyBrown(0xBC8F8F);
    const Color Color::IndianRed(0xCD5C5C);
    const Color Color::Red(0xFF0000);
    const Color Color::Brown(0xA52A2A);
    const Color Color::FireBrick(0xB22222);
    const Color Color::DarkRed(0x8B0000);
    const Color Color::Maroon(0x800000);
    const Color Color::White(0xFFFFFF);
    const Color Color::WhiteSmoke(0xF5F5F5);
    const Color Color::Gainsboro(0xDCDCDC);
    const Color Color::LightGrey(0xD3D3D3);
    const Color Color::Silver(0xC0C0C0);
    const Color Color::DarkGray(0xA9A9A9);
    const Color Color::Gray(0x808080);
    const Color Color::DimGray(0x696969);
    const Color Color::Black(0x000000);

}