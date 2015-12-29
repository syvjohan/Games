#ifndef COLOR_H
#define COLOR_H

#include "gamemath.h"
#include <cstdio>

struct Color
{
    float r, g, b, a;

    // Default ctor
    Color() { r = 0; g = 0; b = 0; a = 0; }

    Color(float r, float g, float b, float a = 1.0f)
    {
        this->r = r;
        this->g = g;
        this->b = b;
        this->a = a;
    }

    // From 0-255 byte values
    Color(int r, int g, int b, int a = 255)
    {
        this->r = r / 255.0f;
        this->g = g / 255.0f;
        this->b = b / 255.0f;
        this->a = a / 255.0f;
    }

    explicit Color(int col)
    {
        r = ((col >> 24) & 0xFF) / 255.0f;
        g = ((col >> 16) & 0xFF) / 255.0f;
        b = ((col >> 8) & 0xFF) / 255.0f;
        a = ((col >> 0) & 0xFF) / 255.0f;
    }

    inline int asInt32() const
    {
        unsigned char col[4];
        col[0] = (unsigned char)(b * 255.0f);
        col[1] = (unsigned char)(g * 255.0f);
        col[2] = (unsigned char)(r * 255.0f);
        col[3] = (unsigned char)(a * 255.0f);
        return *((int*)col);
    }

    inline Vec4 asFloats() const {
        return Vec4(r, g, b, a);
    }

    inline operator Vec4() const {
        return asFloats();
    }

    // Static constant colors
    static const Color  AliceBlue;
    static const Color  AntiqueWhite;
    static const Color  Aqua;
    static const Color  Aquamarine;
    static const Color  Azure;
    static const Color  Beige;
    static const Color  Bisque;
    static const Color  Black;
    static const Color  BlanchedAlmond;
    static const Color  Blue;
    static const Color  BlueViolet;
    static const Color  Brown;
    static const Color  BurlyWood;
    static const Color  CadetBlue;
    static const Color  Chartreuse;
    static const Color  Chocolate;
    static const Color  Coral;
    static const Color  CornflowerBlue;
    static const Color  Cornsilk;
    static const Color  Crimson;
    static const Color  Cyan;
    static const Color  DarkBlue;
    static const Color  DarkCyan;
    static const Color  DarkGoldenrod;
    static const Color  DarkGray;
    static const Color  DarkGreen;
    static const Color  DarkKhaki;
    static const Color  DarkMagenta;
    static const Color  DarkOliveGreen;
    static const Color  DarkOrange;
    static const Color  DarkOrchid;
    static const Color  DarkRed;
    static const Color  DarkSalmon;
    static const Color  DarkSeaGreen;
    static const Color  DarkSlateBlue;
    static const Color  DarkSlateGray;
    static const Color  DarkTurquoise;
    static const Color  DarkViolet;
    static const Color  DeepPink;
    static const Color  DeepSkyBlue;
    static const Color  DimGray;
    static const Color  DodgerBlue;
    static const Color  Firebrick;
    static const Color  FloralWhite;
    static const Color  ForestGreen;
    static const Color  Fuchsia;
    static const Color  Gainsboro;
    static const Color  GhostWhite;
    static const Color  Gold;
    static const Color  Goldenrod;
    static const Color  Gray;
    static const Color  Green;
    static const Color  GreenYellow;
    static const Color  Honeydew;
    static const Color  HotPink;
    static const Color  IndianRed;
    static const Color  Indigo;
    static const Color  Ivory;
    static const Color  Khaki;
    static const Color  Lavender;
    static const Color  LavenderBlush;
    static const Color  LawnGreen;
    static const Color  LemonChiffon;
    static const Color  LightBlue;
    static const Color  LightCoral;
    static const Color  LightCyan;
    static const Color  LightGoldenrodYellow;
    static const Color  LightGray;
    static const Color  LightGreen;
    static const Color  LightPink;
    static const Color  LightSalmon;
    static const Color  LightSeaGreen;
    static const Color  LightSkyBlue;
    static const Color  LightSlateGray;
    static const Color  LightSteelBlue;
    static const Color  LightYellow;
    static const Color  Lime;
    static const Color  LimeGreen;
    static const Color  Linen;
    static const Color  Magenta;
    static const Color  Maroon;
    static const Color  MediumAquamarine;
    static const Color  MediumBlue;
    static const Color  MediumOrchid;
    static const Color  MediumPurple;
    static const Color  MediumSeaGreen;
    static const Color  MediumSlateBlue;
    static const Color  MediumSpringGreen;
    static const Color  MediumTurquoise;
    static const Color  MediumVioletRed;
    static const Color  MidnightBlue;
    static const Color  MintCream;
    static const Color  MistyRose;
    static const Color  Moccasin;
    static const Color  NavajoWhite;
    static const Color  Navy;
    static const Color  OldLace;
    static const Color  Olive;
    static const Color  OliveDrab;
    static const Color  Orange;
    static const Color  OrangeRed;
    static const Color  Orchid;
    static const Color  PaleGoldenrod;
    static const Color  PaleGreen;
    static const Color  PaleTurquoise;
    static const Color  PaleVioletRed;
    static const Color  PapayaWhip;
    static const Color  PeachPuff;
    static const Color  Peru;
    static const Color  Pink;
    static const Color  Plum;
    static const Color  PowderBlue;
    static const Color  Purple;
    static const Color  Red;
    static const Color  RosyBrown;
    static const Color  RoyalBlue;
    static const Color  SaddleBrown;
    static const Color  Salmon;
    static const Color  SandyBrown;
    static const Color  SeaGreen;
    static const Color  SeaShell;
    static const Color  Sienna;
    static const Color  Silver;
    static const Color  SkyBlue;
    static const Color  SlateBlue;
    static const Color  SlateGray;
    static const Color  Snow;
    static const Color  SpringGreen;
    static const Color  SteelBlue;
    static const Color  Tan;
    static const Color  Teal;
    static const Color  Thistle;
    static const Color  Tomato;
    static const Color  Transparent;
    static const Color  Turquoise;
    static const Color  Violet;
    static const Color  Wheat;
    static const Color  White;
    static const Color  WhiteSmoke;
    static const Color  Yellow;
    static const Color  YellowGreen;
};

enum ColorPreset
{
    AliceBlue = (240 << 24) | (248 << 16) | (255 << 8) | 255,
    AntiqueWhite = (250 << 24) | (235 << 16) | (215 << 8) | 255,
    Aqua = (0 << 24) | (255 << 16) | (255 << 8) | 255,
    Aquamarine = (127 << 24) | (255 << 16) | (212 << 8) | 255,
    Azure = (240 << 24) | (255 << 16) | (255 << 8) | 255,
    Beige = (245 << 24) | (245 << 16) | (220 << 8) | 255,
    Bisque = (255 << 24) | (228 << 16) | (196 << 8) | 255,
    Black = (0 << 24) | (0 << 16) | (0 << 8) | 255,
    BlanchedAlmond = (255 << 24) | (235 << 16) | (205 << 8) | 255,
    Blue = (0 << 24) | (0 << 16) | (255 << 8) | 255,
    BlueViolet = (138 << 24) | (43 << 16) | (226 << 8) | 255,
    Brown = (165 << 24) | (42 << 16) | (42 << 8) | 255,
    BurlyWood = (222 << 24) | (184 << 16) | (135 << 8) | 255,
    CadetBlue = (95 << 24) | (158 << 16) | (160 << 8) | 255,
    Chartreuse = (127 << 24) | (255 << 16) | (0 << 8) | 255,
    Chocolate = (210 << 24) | (105 << 16) | (30 << 8) | 255,
    Coral = (255 << 24) | (127 << 16) | (80 << 8) | 255,
    CornflowerBlue = (100 << 24) | (149 << 16) | (237 << 8) | 255,
    Cornsilk = (255 << 24) | (248 << 16) | (220 << 8) | 255,
    Crimson = (220 << 24) | (20 << 16) | (60 << 8) | 255,
    Cyan = (0 << 24) | (255 << 16) | (255 << 8) | 255,
    DarkBlue = (0 << 24) | (0 << 16) | (139 << 8) | 255,
    DarkCyan = (0 << 24) | (139 << 16) | (139 << 8) | 255,
    DarkGoldenrod = (184 << 24) | (134 << 16) | (11 << 8) | 255,
    DarkGray = (169 << 24) | (169 << 16) | (169 << 8) | 255,
    DarkGreen = (0 << 24) | (100 << 16) | (0 << 8) | 255,
    DarkKhaki = (189 << 24) | (183 << 16) | (107 << 8) | 255,
    DarkMagenta = (139 << 24) | (0 << 16) | (139 << 8) | 255,
    DarkOliveGreen = (85 << 24) | (107 << 16) | (47 << 8) | 255,
    DarkOrange = (255 << 24) | (140 << 16) | (0 << 8) | 255,
    DarkOrchid = (153 << 24) | (50 << 16) | (204 << 8) | 255,
    DarkRed = (139 << 24) | (0 << 16) | (0 << 8) | 255,
    DarkSalmon = (233 << 24) | (150 << 16) | (122 << 8) | 255,
    DarkSeaGreen = (143 << 24) | (188 << 16) | (139 << 8) | 255,
    DarkSlateBlue = (72 << 24) | (61 << 16) | (139 << 8) | 255,
    DarkSlateGray = (47 << 24) | (79 << 16) | (79 << 8) | 255,
    DarkTurquoise = (0 << 24) | (206 << 16) | (209 << 8) | 255,
    DarkViolet = (148 << 24) | (0 << 16) | (211 << 8) | 255,
    DeepPink = (255 << 24) | (20 << 16) | (147 << 8) | 255,
    DeepSkyBlue = (0 << 24) | (191 << 16) | (255 << 8) | 255,
    DimGray = (105 << 24) | (105 << 16) | (105 << 8) | 255,
    DodgerBlue = (30 << 24) | (144 << 16) | (255 << 8) | 255,
    Firebrick = (178 << 24) | (34 << 16) | (34 << 8) | 255,
    FloralWhite = (255 << 24) | (250 << 16) | (240 << 8) | 255,
    ForestGreen = (34 << 24) | (139 << 16) | (34 << 8) | 255,
    Fuchsia = (255 << 24) | (0 << 16) | (255 << 8) | 255,
    Gainsboro = (220 << 24) | (220 << 16) | (220 << 8) | 255,
    GhostWhite = (248 << 24) | (248 << 16) | (255 << 8) | 255,
    Gold = (255 << 24) | (215 << 16) | (0 << 8) | 255,
    Goldenrod = (218 << 24) | (165 << 16) | (32 << 8) | 255,
    Gray = (128 << 24) | (128 << 16) | (128 << 8) | 255,
    Green = (0 << 24) | (128 << 16) | (0 << 8) | 255,
    GreenYellow = (173 << 24) | (255 << 16) | (47 << 8) | 255,
    Honeydew = (240 << 24) | (255 << 16) | (240 << 8) | 255,
    HotPink = (255 << 24) | (105 << 16) | (180 << 8) | 255,
    IndianRed = (205 << 24) | (92 << 16) | (92 << 8) | 255,
    Indigo = (75 << 24) | (0 << 16) | (130 << 8) | 255,
    Ivory = (255 << 24) | (255 << 16) | (240 << 8) | 255,
    Khaki = (240 << 24) | (230 << 16) | (140 << 8) | 255,
    Lavender = (230 << 24) | (230 << 16) | (250 << 8) | 255,
    LavenderBlush = (255 << 24) | (240 << 16) | (245 << 8) | 255,
    LawnGreen = (124 << 24) | (252 << 16) | (0 << 8) | 255,
    LemonChiffon = (255 << 24) | (250 << 16) | (205 << 8) | 255,
    LightBlue = (173 << 24) | (216 << 16) | (230 << 8) | 255,
    LightCoral = (240 << 24) | (128 << 16) | (128 << 8) | 255,
    LightCyan = (224 << 24) | (255 << 16) | (255 << 8) | 255,
    LightGoldenrodYellow = (250 << 24) | (250 << 16) | (210 << 8) | 255,
    LightGray = (211 << 24) | (211 << 16) | (211 << 8) | 255,
    LightGreen = (144 << 24) | (238 << 16) | (144 << 8) | 255,
    LightPink = (255 << 24) | (182 << 16) | (193 << 8) | 255,
    LightSalmon = (255 << 24) | (160 << 16) | (122 << 8) | 255,
    LightSeaGreen = (32 << 24) | (178 << 16) | (170 << 8) | 255,
    LightSkyBlue = (135 << 24) | (206 << 16) | (250 << 8) | 255,
    LightSlateGray = (119 << 24) | (136 << 16) | (153 << 8) | 255,
    LightSteelBlue = (176 << 24) | (196 << 16) | (222 << 8) | 255,
    LightYellow = (255 << 24) | (255 << 16) | (224 << 8) | 255,
    Lime = (0 << 24) | (255 << 16) | (0 << 8) | 255,
    LimeGreen = (50 << 24) | (205 << 16) | (50 << 8) | 255,
    Linen = (250 << 24) | (240 << 16) | (230 << 8) | 255,
    Magenta = (255 << 24) | (0 << 16) | (255 << 8) | 255,
    Maroon = (128 << 24) | (0 << 16) | (0 << 8) | 255,
    MediumAquamarine = (102 << 24) | (205 << 16) | (170 << 8) | 255,
    MediumBlue = (0 << 24) | (0 << 16) | (205 << 8) | 255,
    MediumOrchid = (186 << 24) | (85 << 16) | (211 << 8) | 255,
    MediumPurple = (147 << 24) | (112 << 16) | (219 << 8) | 255,
    MediumSeaGreen = (60 << 24) | (179 << 16) | (113 << 8) | 255,
    MediumSlateBlue = (123 << 24) | (104 << 16) | (238 << 8) | 255,
    MediumSpringGreen = (0 << 24) | (250 << 16) | (154 << 8) | 255,
    MediumTurquoise = (72 << 24) | (209 << 16) | (204 << 8) | 255,
    MediumVioletRed = (199 << 24) | (21 << 16) | (133 << 8) | 255,
    MidnightBlue = (25 << 24) | (25 << 16) | (112 << 8) | 255,
    MintCream = (245 << 24) | (255 << 16) | (250 << 8) | 255,
    MistyRose = (255 << 24) | (228 << 16) | (225 << 8) | 255,
    Moccasin = (255 << 24) | (228 << 16) | (181 << 8) | 255,
    NavajoWhite = (255 << 24) | (222 << 16) | (173 << 8) | 255,
    Navy = (0 << 24) | (128 << 16) | (255 << 8) | 255,
    OldLace = (253 << 24) | (245 << 16) | (230 << 8) | 255,
    Olive = (128 << 24) | (128 << 16) | (0 << 8) | 255,
    OliveDrab = (107 << 24) | (142 << 16) | (35 << 8) | 255,
    Orange = (255 << 24) | (165 << 16) | (0 << 8) | 255,
    OrangeRed = (255 << 24) | (69 << 16) | (0 << 8) | 255,
    Orchid = (218 << 24) | (112 << 16) | (214 << 8) | 255,
    PaleGoldenrod = (238 << 24) | (232 << 16) | (170 << 8) | 255,
    PaleGreen = (152 << 24) | (251 << 16) | (152 << 8) | 255,
    PaleTurquoise = (175 << 24) | (238 << 16) | (238 << 8) | 255,
    PaleVioletRed = (219 << 24) | (112 << 16) | (147 << 8) | 255,
    PapayaWhip = (255 << 24) | (239 << 16) | (213 << 8) | 255,
    PeachPuff = (255 << 24) | (218 << 16) | (185 << 8) | 255,
    Peru = (205 << 24) | (133 << 16) | (63 << 8) | 255,
    Pink = (255 << 24) | (192 << 16) | (203 << 8) | 255,
    Plum = (221 << 24) | (160 << 16) | (221 << 8) | 255,
    PowderBlue = (176 << 24) | (224 << 16) | (230 << 8) | 255,
    Purple = (128 << 24) | (0 << 16) | (128 << 8) | 255,
    Red = (255 << 24) | (0 << 16) | (0 << 8) | 255,
    RosyBrown = (188 << 24) | (143 << 16) | (143 << 8) | 255,
    RoyalBlue = (65 << 24) | (105 << 16) | (225 << 8) | 255,
    SaddleBrown = (139 << 24) | (69 << 16) | (19 << 8) | 255,
    Salmon = (250 << 24) | (128 << 16) | (114 << 8) | 255,
    SandyBrown = (244 << 24) | (164 << 16) | (96 << 8) | 255,
    SeaGreen = (46 << 24) | (139 << 16) | (87 << 8) | 255,
    SeaShell = (255 << 24) | (245 << 16) | (238 << 8) | 255,
    Sienna = (160 << 24) | (82 << 16) | (45 << 8) | 255,
    Silver = (192 << 24) | (192 << 16) | (192 << 8) | 255,
    SkyBlue = (135 << 24) | (206 << 16) | (235 << 8) | 255,
    SlateBlue = (106 << 24) | (90 << 16) | (205 << 8) | 255,
    SlateGray = (112 << 24) | (128 << 16) | (144 << 8) | 255,
    Snow = (255 << 24) | (250 << 16) | (250 << 8) | 255,
    SpringGreen = (0 << 24) | (255 << 16) | (127 << 8) | 255,
    SteelBlue = (70 << 24) | (130 << 16) | (180 << 8) | 255,
    Tan = (210 << 24) | (180 << 16) | (140 << 8) | 255,
    Teal = (0 << 24) | (128 << 16) | (128 << 8) | 255,
    Thistle = (216 << 24) | (191 << 16) | (216 << 8) | 255,
    Tomato = (255 << 24) | (99 << 16) | (71 << 8) | 255,
    Transparent = (0 << 24) | (0 << 16) | (0 << 8) | 0,
    Turquoise = (64 << 24) | (224 << 16) | (208 << 8) | 255,
    Violet = (238 << 24) | (130 << 16) | (238 << 8) | 255,
    Wheat = (245 << 24) | (222 << 16) | (179 << 8) | 255,
    White = (255 << 24) | (255 << 16) | (255 << 8) | 255,
    WhiteSmoke = (245 << 24) | (245 << 16) | (245 << 8) | 255,
    Yellow = (255 << 24) | (255 << 16) | (0 << 8) | 255,
    YellowGreen = (154 << 24) | (205 << 16) | (50 << 8) | 255,
};

#endif // !COLOR_H
