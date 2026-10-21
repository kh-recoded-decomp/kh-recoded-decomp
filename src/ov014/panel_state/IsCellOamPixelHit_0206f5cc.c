#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct CellOamData {
    u16 attr0;
    u16 attr1;
    u16 attr2;
} CellOamData;

typedef struct CellData {
    u16 numOams;
    u16 cellAttr;
    CellOamData *oams;
} CellData;

typedef union CellOam {
    CellOamData raw;
    struct {
        u32 attr01;
        u32 attr23;
    } words;
    struct {
        u32 y : 8;
        u32 rsMode : 2;
        u32 objMode : 2;
        u32 mosaic : 1;
        u32 colorMode : 1;
        u32 shape : 2;
        u32 x : 9;
        u32 rsParam : 3;
        u32 flipH : 1;
        u32 flipV : 1;
        u32 size : 2;
        u32 charNo : 10;
        u32 priority : 2;
        u32 cParam : 4;
        u32 pad : 16;
    } bits;
} CellOam;

extern u16 data_02052fd4[4][4];
extern u16 data_02052fbc[4][4];

static inline u32 GetOamShape(const CellOam *oam)
{
    return oam->words.attr01 & 0xc000c000;
}

BOOL IsCellOamPixelHit_0206f5cc(CellData *cell, u16 index, int charBase, fx32 *pos, int px, int py)
{
    CellOam oam;
    BOOL hit;
    fx32 originX;
    fx32 originY;
    int x;
    int y;
    u32 shape;
    int width;
    int height;
    int dx;
    int dy;
    int tile;
    u8 *pixels;

    originX = (pos[0] + 0x800) >> 12;
    oam.raw = cell->oams[index];
    hit = FALSE;
    x = oam.bits.x;
    if (x > 0xff) {
        x |= -0x100;
    }
    x += originX;
    originY = (pos[1] + 0x800) >> 12;
    y = oam.bits.y;
    if (y > 0x7f) {
        y |= ~0x7f;
    }
    y += originY;
    shape = GetOamShape(&oam);
    width = data_02052fd4[(int)(shape & 0xc000) >> 14][(shape & 0xc0000000) >> 30];
    height = data_02052fbc[(int)(shape & 0xc000) >> 14][(shape & 0xc0000000) >> 30];
    if (x <= px && px < x + width && y <= py && py < y + height) {
        dx = px - x;
        dy = py - y;
        if (oam.bits.flipH) {
            dx = width - 1 - dx;
        }
        if (oam.bits.flipV) {
            dy = height - 1 - dy;
        }
        tile = (dy >> 3) * width / 8 + (dx >> 3);
        pixels = (u8 *)(0x06600000 + (u16)(charBase + oam.bits.charNo) * 0x80) + tile * 0x40;
        dx = (dx & 7) + (dy & 7) * 8;
        if (pixels[dx] != 0) {
            hit = TRUE;
        }
    }
    return hit;
}
