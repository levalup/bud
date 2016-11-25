//
// Created by kier on 15-11-18.
//

#ifndef BUD_COLOR_H
#define BUD_COLOR_H

#include <SDL2/SDL_pixels.h>
#include "Util.h"

namespace bud {

    class Color {
    public:
        Color();

        Color(unsigned int code);

        Color(unsigned int code, byte a);

        Color(byte r, byte g, byte b);

        Color(byte r, byte g, byte b, byte a);

        Color(const Color &other);

        virtual ~Color() = default;

        const Color alpha(byte __a) const;

        unsigned int code();

        Color &operator=(const Color &other);

        void raw_fill(SDL_Color *sdl_color) const;

        const SDL_Color meta_color() const;

        byte r;
        byte g;
        byte b;
        byte a;

        static const Color LightPink;
        static const Color Pink;
        static const Color Crimson;
        static const Color LavenderBlush;
        static const Color PaleVioletRed;
        static const Color HotPink;
        static const Color DeepPink;
        static const Color MediumVioletRed;
        static const Color Orchid;
        static const Color Thistle;
        static const Color Plum;
        static const Color Violet;
        static const Color Magenta;
        static const Color Fuchsia;
        static const Color DarkMagenta;
        static const Color Purple;
        static const Color MediumOrchid;
        static const Color DarkVoilet;
        static const Color DarkOrchid;
        static const Color Indigo;
        static const Color BlueViolet;
        static const Color MediumPurple;
        static const Color MediumSlateBlue;
        static const Color SlateBlue;
        static const Color DarkSlateBlue;
        static const Color Lavender;
        static const Color GhostWhite;
        static const Color Blue;
        static const Color MediumBlue;
        static const Color MidnightBlue;
        static const Color DarkBlue;
        static const Color Navy;
        static const Color RoyalBlue;
        static const Color CornflowerBlue;
        static const Color LightSteelBlue;
        static const Color LightSlateGray;
        static const Color SlateGray;
        static const Color DoderBlue;
        static const Color AliceBlue;
        static const Color SteelBlue;
        static const Color LightSkyBlue;
        static const Color SkyBlue;
        static const Color DeepSkyBlue;
        static const Color LightBLue;
        static const Color PowDerBlue;
        static const Color CadetBlue;
        static const Color Azure;
        static const Color LightCyan;
        static const Color PaleTurquoise;
        static const Color Cyan;
        static const Color Aqua;
        static const Color DarkTurquoise;
        static const Color DarkSlateGray;
        static const Color DarkCyan;
        static const Color Teal;
        static const Color MediumTurquoise;
        static const Color LightSeaGreen;
        static const Color Turquoise;
        static const Color Auqamarin;
        static const Color MediumAquamarine;
        static const Color MediumSpringGreen;
        static const Color MintCream;
        static const Color SpringGreen;
        static const Color SeaGreen;
        static const Color Honeydew;
        static const Color LightGreen;
        static const Color PaleGreen;
        static const Color DarkSeaGreen;
        static const Color LimeGreen;
        static const Color Lime;
        static const Color ForestGreen;
        static const Color Green;
        static const Color DarkGreen;
        static const Color Chartreuse;
        static const Color LawnGreen;
        static const Color GreenYellow;
        static const Color OliveDrab;
        static const Color Beige;
        static const Color LightGoldenrodYellow;
        static const Color Ivory;
        static const Color LightYellow;
        static const Color Yellow;
        static const Color Olive;
        static const Color DarkKhaki;
        static const Color LemonChiffon;
        static const Color PaleGodenrod;
        static const Color Khaki;
        static const Color Gold;
        static const Color Cornislk;
        static const Color GoldEnrod;
        static const Color FloralWhite;
        static const Color OldLace;
        static const Color Wheat;
        static const Color Moccasin;
        static const Color Orange;
        static const Color PapayaWhip;
        static const Color BlanchedAlmond;
        static const Color NavajoWhite;
        static const Color AntiqueWhite;
        static const Color Tan;
        static const Color BrulyWood;
        static const Color Bisque;
        static const Color DarkOrange;
        static const Color Linen;
        static const Color Peru;
        static const Color PeachPuff;
        static const Color SandyBrown;
        static const Color Chocolate;
        static const Color SaddleBrown;
        static const Color SeaShell;
        static const Color Sienna;
        static const Color LightSalmon;
        static const Color Coral;
        static const Color OrangeRed;
        static const Color DarkSalmon;
        static const Color Tomato;
        static const Color MistyRose;
        static const Color Salmon;
        static const Color Snow;
        static const Color LightCoral;
        static const Color RosyBrown;
        static const Color IndianRed;
        static const Color Red;
        static const Color Brown;
        static const Color FireBrick;
        static const Color DarkRed;
        static const Color Maroon;
        static const Color White;
        static const Color WhiteSmoke;
        static const Color Gainsboro;
        static const Color LightGrey;
        static const Color Silver;
        static const Color DarkGray;
        static const Color Gray;
        static const Color DimGray;
        static const Color Black;
    };

}


#endif //BUD_COLOR_H
