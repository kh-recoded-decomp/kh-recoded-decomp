#include "nitro/types.h"

typedef struct TileTable {
    int *ids;
    int count;
    u16 width;
    u16 height;
    u16 rowLength;
    u8 pad_0E[2];
    u16 *rows;
    int loadImmediately;
    u8 dirtyMask;
    u8 pad_19[3];
} TileTable;

extern u16 *GetTileTableRow_020b9948(TileTable *table, int id, int *indexOut);
extern void func_01ff8684(u32 value, void *dst, u32 size);

void ClearTileTableRect_020b9d54(TileTable *table, int id, int x, int y, int width, int height)
{
    int i;
    int index;
    u16 *row = GetTileTableRow_020b9948(table, id, &index);

    if (row == NULL) {
        return;
    }
    if (width + x > table->width) {
        width = table->width - x;
    }
    for (i = 0; i < height; i++) {
        func_01ff8684(0, &row[table->width * (y + i) + x], width * 2);
    }
    table->dirtyMask |= 1 << index;
}

