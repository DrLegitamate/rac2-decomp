#include "include_asm.h"
typedef unsigned char u8;
typedef unsigned long u64;
typedef int s32;
extern void func_002FC560(unsigned int,unsigned long);
/* Adapted from RAC1 draw.c func_001F6668_r (GPL-3.0), the FontPrint counterpart. */
struct Glyph_F6668 { u8 u,v; signed char top,adv; };
extern int D_001B166C;
extern int D_001B1668 __attribute__((sda));
extern int D_001A89B0[8] __attribute__((sda));
extern void func_0027E018(int,int,int,int,int,int,int,int,long,long);
void func_0027F2A8(s32 x, s32 y, u64 color, u8 *text, s32 character_limit, u64 texture,
                      u8 *metrics) {
    struct Glyph_F6668 *glyphs = (struct Glyph_F6668 *)metrics;
    s32 character_count;
    u8 *cursor;
    u8 character;
    struct Glyph_F6668 *overlay_glyph;
    s32 gray_value;
    s32 gray_color;

    if (D_001B166C == 0) {
        D_001A89B0[0] = color;
    }
    func_002FC560(0x47, 0x33001);
    character_count = 0;
    if (character_limit == 0 || *text == 0) {
        return;
    }
    cursor = text;
    do {
        /* Bytes 8..15 select a palette color, preserving the current alpha. */
        if ((u8)(*cursor - 8) < 8) {
            if (D_001B1668 != 0) {
                color &= 0xFF000000;
                color |= D_001A89B0[*cursor - 8] & 0xFFFFFF;
            }
        } else {
            character = *cursor;
            if (glyphs[character].adv != 0) {
                /* Characters 0x80..0xa7 also draw the glyph 0x40 entries later. */
                if ((u8)(character + 0x80) < 0x28) {
                    overlay_glyph = (struct Glyph_F6668 *)(((character + 0x40) << 2) + (s32)glyphs);
                    func_0027E018(x + overlay_glyph->adv, y + overlay_glyph->top, 16, 16,
                                       overlay_glyph->u, overlay_glyph->v, 16, 16, color, texture);
                }
                /* Control glyphs use 24-pixel grayscale sprites. */
                if (*cursor < 0x20) {
                    gray_value =
                        (s32)((color & 0xFF) + ((color >> 8) & 0xFF) + ((color >> 16) & 0xFF)) / 3;
                    gray_color = (s32)(color & 0xFF000000);
                    gray_color += gray_value << 16;
                    gray_color += gray_value << 8;
                    gray_value += gray_color;
                    func_0027E018(x, y + glyphs[*cursor].top, 24, 16, glyphs[*cursor].u,
                                       glyphs[*cursor].v, 24, 16, gray_value, texture);
                } else if (*cursor > 0x20) {
                    func_0027E018(x, y + glyphs[*cursor].top, 16, 16, glyphs[*cursor].u,
                                       glyphs[*cursor].v, 16, 16, color, texture);
                }
                x += glyphs[*cursor].adv;
            }
        }
        character_count++;
        if (character_count == character_limit) {
            break;
        }
        cursor++;
    } while (*cursor != 0);
}
