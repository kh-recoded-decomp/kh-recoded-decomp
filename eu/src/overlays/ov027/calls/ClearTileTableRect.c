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

extern u16 *GetTileTableRow(TileTable *table, int id, int *indexOut);
extern void MIi_CpuClear16(u32 value, void *dst, u32 size);

void ClearTileTableRect(TileTable *table, int id, int x, int y, int width, int height)
{
    int i;
    int index;
    u16 *row = GetTileTableRow(table, id, &index);

    if (row == NULL) {
        return;
    }
    if (width + x > table->width) {
        width = table->width - x;
    }
    for (i = 0; i < height; i++) {
        MIi_CpuClear16(0, &row[table->width * (y + i) + x], width * 2);
    }
    table->dirtyMask |= 1 << index;
}
