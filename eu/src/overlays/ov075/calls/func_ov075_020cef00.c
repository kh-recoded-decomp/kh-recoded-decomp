#pragma opt_propagation off
#include "nitro/types.h"

typedef struct {
    u16 left;
    u16 middle;
    u16 right;
} FrameRowTiles;

typedef struct {
    FrameRowTiles rows[3];
} FrameTiles;

extern FrameTiles sFrameTiles;
extern void func_01ff88c4(void *dest, int value, u32 size);
extern void MIi_CpuClear16(u16 value, void *dest, u32 size);

void func_ov075_020cef00(int x, int y, int width, int height, u16 (*screen)[32])
{
    FrameTiles tiles = sFrameTiles;
    u16 left = x;
    u16 top = y;
    u16 frameWidth;
    u16 frameHeight;
    int row;
    int bottom;

    if (width > 32 - left) {
        width = 32 - left;
    }
    frameWidth = width;
    if (height > 24 - top) {
        height = 24 - top;
    }
    frameHeight = height;
    bottom = top + frameHeight;

    func_01ff88c4(screen, 0, top * sizeof(screen[0]));
    for (row = top; row < bottom; row++) {
        int kind;

        if (row == top) {
            kind = 0;
        } else if (row == top + frameHeight - 1) {
            kind = 2;
        } else {
            kind = 1;
        }
        func_01ff88c4(screen[row], 0, left * 2);
        screen[row][left] = tiles.rows[kind].left;
        MIi_CpuClear16(tiles.rows[kind].middle, &screen[row][left + 1], (frameWidth - 2) * 2);
        screen[row][left + frameWidth - 1] = tiles.rows[kind].right;
        func_01ff88c4(&screen[row][left + frameWidth], 0, (32 - (left + frameWidth)) * 2);
    }
    func_01ff88c4(screen[top + frameHeight], 0, (24 - (top + frameHeight)) * sizeof(screen[0]));
}
