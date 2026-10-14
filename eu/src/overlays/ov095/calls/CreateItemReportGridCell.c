#include "nitro/types.h"

typedef struct ItemReportGridCell {
    int itemIndex;
    int x;
    int y;
} ItemReportGridCell;

typedef struct ItemReportGrid {
    u8 unknown00[0x20];
    ItemReportGridCell **cells;
    int width;
} ItemReportGrid;

typedef struct ItemReportMenu {
    u8 unknown00[0x110a4];
    ItemReportGrid grid;
} ItemReportMenu;

extern void *NNS_FndAllocFromDefaultExpHeapEx(u32 size, int alignment);

#define GRID_CELL_AT(cells, offset) \
    (*(ItemReportGridCell **)((u8 *)(cells) + (offset)))

void CreateItemReportGridCell(int column, int row, int itemIndex, int x,
                            int y, ItemReportMenu *menu)
{
    ItemReportGrid *grid = &menu->grid;
    long cellOffset = (row * grid->width + column) * sizeof(ItemReportGridCell *);
    ItemReportGridCell **cells = grid->cells;

    GRID_CELL_AT(cells, cellOffset) =
        NNS_FndAllocFromDefaultExpHeapEx(sizeof(ItemReportGridCell), -4);
    GRID_CELL_AT(cells, cellOffset)->x = x;
    GRID_CELL_AT(cells, cellOffset)->y = y;
    GRID_CELL_AT(cells, cellOffset)->itemIndex = itemIndex;
}

#undef GRID_CELL_AT
