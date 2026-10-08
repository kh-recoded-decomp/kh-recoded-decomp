#include "nitro/types.h"

typedef struct {
    u16 id;
    u8 type;
    s8 linkIndex;
    s16 slotId;
    u16 groupBit;
    u8 placed;
    u8 pad_09[0x14 - 9];
} GridItem;

typedef struct {
    u8 pad_00[0x18];
    GridItem *links[32];
    u8 *dims;
} Grid;

extern u8 *data_0205fe0c;
extern int GetPackedBitMask(int *bitWords, int bitIndex);

static inline void SetPixel(u8 *pixels, u16 x, u16 y, u8 color)
{
    u8 *cell = pixels + ((y & 7) * 4 + (y >> 3) * 0x300 + (x >> 3) * 32 + ((x & 7) >> 1));
    u8 shift = (x & 1) << 2;
    int value = (color & 0xf) << shift;
    *cell = (*cell & (0xf0 >> shift)) | value;
}

static inline void SetPixelByte(u8 *pixels, u16 x, u16 y, u8 color)
{
    pixels[(y & 7) * 4 + (y >> 3) * 0x300 + (x >> 3) * 32 + ((x & 7) >> 1)] = color;
}

static inline void SetPixelRow(u8 *pixels, u16 x, u16 y, u8 color)
{
    u8 *cell = pixels + ((y & 7) * 4 + (y >> 3) * 0x300 + (x >> 3) * 32 + ((x & 7) >> 1));
    cell[0] = cell[1] = color;
}

void DrawMatrixCellGlyph_020c7fa8(u8 *pixels, Grid *grid, GridItem *item, u32 cellIndex)
{
    u8 columns = *grid->dims;
    u8 type = item->type;
    s16 index = item->linkIndex;
    BOOL unlocked;
    u16 left;
    int x; // int copy keeps the u16 truncation per call
    int top;
    u8 color;

    if (index >= 0 && item >= grid->links[0]) {
        index = item - grid->links[0];
    }
    if (index >= 0) {
        unlocked = GetPackedBitMask((int *)(data_0205fe0c + 0x2c5c), index) ? TRUE : FALSE;
        if (!unlocked) {
            item = grid->links[index];
            type = item->type;
        } else if (item->type == 4 || item->type == 5) {
            return;
        }
    }
    left = (cellIndex % columns) * 4;
    x = left;
    top = (u16)((cellIndex / columns) * 4);
    if (item->placed == 0) {
        color = 0xaa;
    } else {
        color = 0x99;
    }

    switch (type) {
    case 0xe:
        SetPixel(pixels, x + 1, top, color);
        SetPixel(pixels, x + 1, top + 1, color);
        SetPixelByte(pixels, x, top + 2, color);
        return;
    case 0xf:
        SetPixel(pixels, x + 1, top, color);
        SetPixel(pixels, x + 1, top + 1, color);
        SetPixel(pixels, x + 1, top + 2, color);
        SetPixelByte(pixels, x + 2, top + 2, color);
        return;
    case 0x10:
        SetPixelByte(pixels, x + 2, top + 2, color);
        SetPixel(pixels, x + 1, top + 2, color);
        SetPixel(pixels, x + 1, top + 3, color);
        return;
    case 0x11:
        SetPixelByte(pixels, x, top + 2, color);
        SetPixel(pixels, x + 1, top + 3, color);
        return;
    case 0x12:
        SetPixelRow(pixels, x, top + 2, color);
        return;
    case 0x13:
        SetPixel(pixels, x + 1, top, color);
        SetPixel(pixels, x + 1, top + 1, color);
        SetPixel(pixels, x + 1, top + 2, color);
        SetPixel(pixels, x + 1, top + 3, color);
        return;
    case 0x14:
        SetPixel(pixels, x + 1, top, color);
        SetPixel(pixels, x + 1, top + 1, color);
        SetPixelByte(pixels, x, top + 2, color);
        SetPixel(pixels, x + 1, top + 3, color);
        return;
    case 0x15:
        SetPixel(pixels, x + 1, top, color);
        SetPixel(pixels, x + 1, top + 1, color);
        SetPixelRow(pixels, x, top + 2, color);
        return;
    case 0x16:
        SetPixel(pixels, x + 1, top, color);
        SetPixel(pixels, x + 1, top + 1, color);
        SetPixel(pixels, x + 1, top + 2, color);
        SetPixel(pixels, x + 1, top + 3, color);
        SetPixelByte(pixels, x + 2, top + 2, color);
        return;
    case 0x17:
        SetPixelRow(pixels, x, top + 2, color);
        SetPixel(pixels, x + 1, top + 3, color);
        return;
    case 0x18:
        SetPixel(pixels, x + 1, top, color);
        SetPixel(pixels, x + 1, top + 1, color);
        SetPixelRow(pixels, x, top + 2, color);
        SetPixel(pixels, x + 1, top + 3, color);
        return;
    case 0:
        color = 0;
        break;
    case 1:
        color = item->slotId >= 0 ? 0x33 : 0x11;
        break;
    case 2:
        color = item->slotId >= 0 ? 0x33 : 0x22;
        break;
    case 3:
        color = 0x44;
        break;
    case 9:
    case 10:
    case 11:
    case 12:
    case 13:
    case 0x19:
        color = 0x55;
        break;
    case 4:
        color = 0xbb;
        break;
    case 5:
        color = 0xcc;
        break;
    case 6:
        color = 0x66;
        break;
    case 7:
        color = 0x77;
        break;
    case 8:
        color = 0x88;
        break;
    }
    SetPixelRow(pixels, left, top, color);
    SetPixelRow(pixels, left, top + 1, color);
    SetPixelRow(pixels, left, top + 2, color);
    SetPixelRow(pixels, left, top + 3, color);
}
