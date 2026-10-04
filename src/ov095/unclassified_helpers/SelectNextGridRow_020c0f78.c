#include "nitro/types.h"

typedef struct {
    int value;
    int x;
    int y;
} GridCell;

typedef struct {
    u8 pad[0x24];
    int width;
    int height;
    int count;
    int cursor;
    int scroll;
} GridTable;

typedef struct {
    int selected;
    u8 pad[0x110a4 - 4];
    GridTable table;
} GridWork;

extern GridCell *GetGridCell_020c0a48(int column, int row, GridWork *work);
extern void SetGridEntryPosition_020c02fc(int layer, int index, int x, int y, GridWork *work);

BOOL SelectNextGridRow_020c0f78(GridWork *work) {
    GridTable *table = &work->table;
    int startRow = table->cursor / table->width;
    GridCell *cell = GetGridCell_020c0a48(table->cursor % table->width, startRow, work);
    int column;
    int row;

    do {
        table->cursor++;
        column = table->cursor % table->width;
        row = table->cursor / table->width;
        cell = GetGridCell_020c0a48(column, row, work);
    } while (cell == NULL);
    if (row != startRow) {
        row--;
        cell = GetGridCell_020c0a48(column, row, work);
    }
    SetGridEntryPosition_020c02fc(0, 3, cell->x, cell->y - table->scroll, work);
    table->cursor = table->width * row + column;
    work->selected = cell->value;
    return TRUE;
}