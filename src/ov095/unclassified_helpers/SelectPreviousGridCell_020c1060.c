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

BOOL SelectPreviousGridCell_020c1060(GridWork *work) {
    GridTable *table = &work->table;
    GridCell *cell;
    int startRow;
    int column;
    int row;

    startRow = table->cursor / table->width;
    cell = GetGridCell_020c0a48(table->cursor % table->width, startRow, work);

    while (TRUE) {
        if (--table->cursor < 0) {
            table->cursor = table->width;
            continue;
        }
        column = table->cursor % table->width;
        row = table->cursor / table->width;
        cell = GetGridCell_020c0a48(column, row, work);
        if (cell == NULL) {
            continue;
        }
        if (row == startRow) {
            break;
        }
        column = table->width - 1;
        table->cursor = table->width * startRow + column;
        row = startRow;
        cell = GetGridCell_020c0a48(column, startRow, work);
        if (cell != NULL) {
            break;
        }
    }
    SetGridEntryPosition_020c02fc(0, 3, cell->x, cell->y - table->scroll, work);
    table->cursor = table->width * row + column;
    work->selected = cell->value;
    return TRUE;
}