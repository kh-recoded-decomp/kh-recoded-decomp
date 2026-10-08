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

typedef struct TileWidget {
    u8 pad_00[0x10];
    int tableId;
} TileWidget;

extern u16 *GetTileTableRow(TileTable *table, int id, int *indexOut);
extern int ClipWidgetToScreen(TileTable *table, TileWidget *widget, int *xOut, int *yOut, int *widthOut, int *heightOut);
extern void MIi_CpuClear16(u32 value, void *dst, u32 size);

void ClearWidgetTileArea(TileTable *table, TileWidget *widget)
{
    int index;
    int x;
    int y;
    int width;
    int height;
    u16 *row;
    int i;
    int stride;

    row = GetTileTableRow(table, widget->tableId, &index);
    if (row == NULL) {
        return;
    }
    stride = ClipWidgetToScreen(table, widget, &x, &y, &width, &height);
    for (i = 0; i < height; i++) {
        MIi_CpuClear16(0, &row[stride * (y + i) + x], width * 2);
    }
    table->dirtyMask |= 1 << index;
}
