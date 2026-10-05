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

typedef struct ScreenSource {
    u8 pad_00[8];
    void *screenData;
} ScreenSource;

typedef struct TileWidget {
    u8 pad_00[2];
    s16 x;
    s16 y;
    u16 srcX;
    u16 srcY;
    u8 pad_0A[6];
    int tableId;
    u8 pad_14[4];
    ScreenSource *source;
} TileWidget;

extern void GetWidgetTileDimensions_020b9970(TileWidget *widget, u32 *widthOut, u32 *heightOut);
extern u16 *GetTileTableRow_020b9948(TileTable *table, int id, int *indexOut);
extern void CopyClippedScreenRegion_020167d0(void *dst, const void *screenData, int srcX, int srcY, int dstX, int dstY, int dstW, int dstH, int width, int height);

void BlitWidgetToTileTable_020b9a74(TileTable *table, TileWidget *widget)
{
    u32 width;
    u32 height;
    int index;
    u16 *row;

    GetWidgetTileDimensions_020b9970(widget, &width, &height);
    row = GetTileTableRow_020b9948(table, widget->tableId, &index);
    if (row == NULL) {
        return;
    }
    CopyClippedScreenRegion_020167d0(row, widget->source->screenData, widget->srcX, widget->srcY, widget->x, widget->y, table->width, table->height, width, height);
    table->dirtyMask |= 1 << index;
}

