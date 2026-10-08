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

extern void GetWidgetTileDimensions(TileWidget *widget, u32 *widthOut, u32 *heightOut);
extern u16 *GetTileTableRow(TileTable *table, int id, int *indexOut);
extern void NNS_G2dBGLoadScreenRect(void *dst, const void *screenData, int srcX, int srcY, int dstX, int dstY, int dstW, int dstH, int width, int height);

void BlitWidgetToTileTable(TileTable *table, TileWidget *widget)
{
    u32 width;
    u32 height;
    int index;
    u16 *row;

    GetWidgetTileDimensions(widget, &width, &height);
    row = GetTileTableRow(table, widget->tableId, &index);
    if (row == NULL) {
        return;
    }
    NNS_G2dBGLoadScreenRect(row, widget->source->screenData, widget->srcX, widget->srcY, widget->x, widget->y, table->width, table->height, width, height);
    table->dirtyMask |= 1 << index;
}
