#pragma opt_common_subs off
#include "nitro/types.h"

typedef struct {
    int id;
    int unk04;
    int y;
} GridCell;

typedef struct {
    int x;
    int y;
    u8 pad_08[0xc];
} GridSlot;

typedef struct {
    int slot;
    u8 pad_04[0x20];
    int width;
    int rows;
    u8 pad_2c[4];
    int pos;
    int scroll;
    int viewTop;
    int viewBottom;
    int scrollTimer;
} GridCursor;

typedef struct {
    int selectedId;
    int hoverId;
    u8 pad_0008[0xc9e4];
    GridSlot slots[1];
} GridScene;

#define GRID_CURSOR(scene) ((GridCursor *)((u8 *)(scene) + 0x110a4))

extern u16 data_02060500;
extern GridCell *GetGridCell_020c0a48(int column, int row, GridScene *owner);
extern void SetGridEntryPosition_020c02fc(int layer, int index, int x, int y, GridScene *scene);
extern void RefreshCursorMarkers_020c1168(GridScene *scene);

BOOL MoveGridCursorDown_020c0ce0(GridScene *scene)
{
    GridCursor *cursor = GRID_CURSOR(scene);
    int wrapped;
    int startPos;
    int moved;
    int width;
    int col;
    int row;
    int stride;
    int pos;
    GridCell *startCell;
    GridCell *cell;
    GridSlot *slot;
    int delta;
    int excess;

    startPos = cursor->pos;
    width = cursor->width;
    col = startPos % width;
    wrapped = 0;
    moved = 0;

    startCell = GetGridCell_020c0a48(col, startPos / width, scene);
    do {
        pos = cursor->pos + cursor->width;
        cursor->pos = pos;
        if (pos >= cursor->width * cursor->rows) {
            if ((data_02060500 & 0x80) && wrapped == 0) {
                moved = 1;
                cursor->pos = col;
                cursor->scroll = 0;
                cursor->scrollTimer = 0;
                startPos = col - cursor->width;
                wrapped++;
            } else {
                cursor->pos = startPos;
                return FALSE;
            }
        }
        stride = cursor->width;
        pos = cursor->pos;
        col = pos % stride;
        row = pos / stride;
        if (row > cursor->rows - 1) {
            cursor->pos -= stride;
            return FALSE;
        }
        cell = GetGridCell_020c0a48(col, row, scene);
    } while (cell == NULL);

    scene->hoverId = cell->id;
    if (cell->y >= cursor->viewBottom + cursor->scroll) {
        cursor->scrollTimer++;
        delta = cursor->scroll + (cell->y - startCell->y);
        cursor->scroll = delta;
        if (delta >= 0x1fa) {
            excess = delta - 0x1fa;
            if (cursor->slot > 0) {
                slot = &scene->slots[cursor->slot];
                slot->y += excess;
                SetGridEntryPosition_020c02fc(0, cursor->slot, slot->x, slot->y, scene);
            }
            cursor->scroll = 0x1fa;
        }
        scene->selectedId = cell->id;
        RefreshCursorMarkers_020c1168(scene);
        return TRUE;
    }

    if (moved == 1) {
        if (cursor->slot > 0) {
            slot = &scene->slots[cursor->slot];
            slot->y = 0x40;
            SetGridEntryPosition_020c02fc(0, cursor->slot, slot->x, slot->y, scene);
        }
        scene->selectedId = cell->id;
        RefreshCursorMarkers_020c1168(scene);
    } else {
        if (cursor->slot > 0) {
            slot = &scene->slots[cursor->slot];
            slot->y += cell->y - startCell->y;
            SetGridEntryPosition_020c02fc(0, cursor->slot, slot->x, slot->y, scene);
        }
        scene->selectedId = cell->id;
    }
    return TRUE;
}
