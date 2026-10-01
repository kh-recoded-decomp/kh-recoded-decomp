#include "nitro/types.h"

typedef struct ByteGrid {
    u8 pad_00[0x44];
    u16 stride;
    u16 height;
    u8 *cells;
    u8 pad_4C[0x18];
    s16 cursorX;
    s16 cursorY;
} ByteGrid;

extern void *NNSi_FndAllocFromDefaultHeap_0202a178(u32 size);
extern void func_01ff8740(u32 value, void *dest, u32 size);

ByteGrid *CreateByteGrid_0207f380(int headerSize, int width, int height)
{
    int stride = (width + 3) / 4 * 4;
    int cellSize = stride * height;
    ByteGrid *grid = NNSi_FndAllocFromDefaultHeap_0202a178(headerSize + cellSize);

    func_01ff8740(0, grid, headerSize + cellSize);
    grid->stride = stride;
    grid->height = height;
    grid->cells = (u8 *)grid + headerSize;
    grid->cursorX = -1;
    grid->cursorY = -1;
    return grid;
}
