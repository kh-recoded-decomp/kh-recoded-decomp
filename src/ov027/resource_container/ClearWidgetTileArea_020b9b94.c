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

extern u16 *GetTileTableRow_020b9948(TileTable *table, int id, int *indexOut);
extern int ClipWidgetToScreen_020b99a0(TileTable *table, TileWidget *widget, int *xOut, int *yOut, int *widthOut, int *heightOut);
extern void func_01ff8684(u32 value, void *dst, u32 size);

void ClearWidgetTileArea_020b9b94(TileTable *table, TileWidget *widget)
{
    int index;
    int x;
    int y;
    int width;
    int height;
    u16 *row;
    int i;
    int stride;

    row = GetTileTableRow_020b9948(table, widget->tableId, &index);
    if (row == NULL) {
        return;
    }
    stride = ClipWidgetToScreen_020b99a0(table, widget, &x, &y, &width, &height);
    for (i = 0; i < height; i++) {
        func_01ff8684(0, &row[stride * (y + i) + x], width * 2);
    }
    table->dirtyMask |= 1 << index;
}

