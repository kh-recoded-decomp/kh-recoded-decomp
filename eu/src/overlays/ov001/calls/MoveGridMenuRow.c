#include "src/overlays/ov001/GridMenuNavigation.h"

extern GridMenuRoot *data_ov001_020a04e4;
extern void DrawGridMenuCells(void *menu, s32 flag);
extern void PlaySoundEffect(s32 sound, s32 arg);

BOOL MoveGridMenuRow(u32 direction)
{
    GridMenuRoot *root = data_ov001_020a04e4;
    GridMenu *menu = &root->menu;
    GridNavigation *grid = &menu->grid;
    BOOL changed = FALSE;
    s32 columns, selected, column, row;
    if (grid->windows == NULL || menu->mode != 6) {
        return FALSE;
    }
    columns = grid->columnCount;
    selected = grid->selectedCell;
    column = selected % columns;
    row = selected / columns;
    switch (direction) {
    case GRID_ROW_UP:
        if (row > 0) {
            row--;
        } else {
            row = grid->rowCount - 1;
        }
        changed = TRUE;
        break;
    case GRID_ROW_DOWN:
        if (row < grid->rowCount - 1) {
            row++;
            changed = TRUE;
            break;
        }
        row = 0;
        changed = TRUE;
        break;
    case GRID_PAGE_UP:
        if (row > 0) {
            grid->firstRow -= grid->pageRows;
            row -= grid->pageRows;
            if (row < 0) {
                grid->firstRow = 0;
                row = 0;
            }
            changed = TRUE;
        }
        break;
    case GRID_PAGE_DOWN:
        if (row < grid->rowCount - 1) {
            grid->firstRow += grid->pageRows;
            row += grid->pageRows;
            if (row > grid->rowCount - 1) {
                grid->firstRow = grid->rowCount - grid->pageRows;
                row = grid->rowCount - 1;
            }
            changed = TRUE;
        }
        break;
    }
    grid->selectedCell = column + row * grid->columnCount;
    if (changed) {
        DrawGridMenuCells(&root->menu, FALSE);
        PlaySoundEffect(0, 0);
    }
    return changed;
}
