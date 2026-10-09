#pragma opt_dead_assignments off
#include "nitro/types.h"

typedef struct GridEntry {
    u16 cell;
    u8 kind;
    s8 linkId;
    u8 pad_04[0x10];
} GridEntry;

typedef struct CursorFrame {
    u8 width;
    u8 height;
    s8 offsetX;
    s8 offsetY;
} CursorFrame;

typedef struct GridMap {
    u8 pad_0000[0x18];
    GridEntry *linked[0x20];
    u8 *columnCount;
    GridEntry *tiles[(0x2be8 - 0x9c) / 4];
    u8 cellLevels[1];
} GridMap;

typedef struct SaveData {
    u8 pad_0000[0x2c5c];
    u8 linkFlags[0x2c67 - 0x2c5c];
    u8 level;
} SaveData;

typedef struct MatrixMenu {
    u8 pad_00000[0x28];
    s16 cursorX;
    s16 cursorY;
    u8 pad_0002c[0x6c - 0x2c];
    int soundEnabled;
    int busy70;
    int busy74;
    int active;
    u8 pad_0007c[0x88 - 0x7c];
    int busy88;
    u8 pad_0008c[0x12dc8 - 0x8c];
    int busy12dc8;
    u8 pad_12dcc[4];
    GridMap *map;
    GridEntry *current;
    u8 pad_12dd8[0x13e64 - 0x12dd8];
    u16 busy13e64;
    u8 pad_13e66[0x13ea0 - 0x13e66];
    int busy13ea0;
    u8 pad_13ea4[0x17524 - 0x13ea4];
    int busy17524;
    int busy17528;
} MatrixMenu;

extern SaveData *data_0205fe0c;
extern const CursorFrame data_ov075_020d1454[];
extern int GetPackedBitMask(void *bits, int index);
extern void PlaySoundEffect_0204d924(int id, int arg);
extern BOOL GetDialogInputMode_020c42b4(MatrixMenu *menu);
extern BOOL IsMatrixInputReady_020caa6c(MatrixMenu *menu);
extern BOOL TracePipePath_020caa98(GridMap *map, GridEntry *tile, int dir, GridEntry **out);
extern GridEntry *func_ov075_020cac34(MatrixMenu *menu, int dir);
extern void ShowEntryHeaderMessage_020cad14(MatrixMenu *menu, GridEntry *entry);
extern void JumpCursorToEntry_020cae58(MatrixMenu *menu, GridEntry *entry, BOOL skipCurrent);
extern BOOL ShowNextUnlockNotice_020cc9fc(MatrixMenu *menu, BOOL eventMode, BOOL queryOnly);

static inline int GetEntryIndex(GridMap *map, GridEntry *entry)
{
    if (entry >= map->linked[0]) {
        return entry - map->linked[0];
    }
    return -1;
}

static inline const CursorFrame *GetCursorFrame(int kind)
{
    int frameIndex;
    int frameOffset;

    if (kind < 3 || kind >= 0xe) {
        frameIndex = 0;
    } else {
        frameIndex = kind - 2;
    }
    frameOffset = frameIndex * sizeof(CursorFrame);
    return (const CursorFrame *)((u8 *)data_ov075_020d1454 + frameOffset);
}

static inline BOOL IsStopKind(GridEntry *entry)
{
    u8 kind = entry->kind;
    BOOL selectable;
    BOOL found;

    found = FALSE;
    selectable = TRUE;
    if ((u8)(kind + 0xfc) <= 0x15 && ((1 << (u8)(kind + 0xfc)) & 0x200003)) {
        selectable = FALSE;
    }
    if (selectable && kind < 0xe) {
        found = TRUE;
    }
    return found;
}

static inline BOOL IsCursorStop(GridMap *map, GridEntry *entry, GridEntry *current)
{
    SaveData *save;
    int index;
    u8 kind;
    u8 shift;
    BOOL found;
    BOOL selectable;

    if (entry != NULL && current != entry && map->cellLevels[entry->cell] <= data_0205fe0c->level) {
        index = GetEntryIndex(map, entry);
        if (index < 0) {
            index = entry->linkId;
        }
        if (index >= 0 && !(GetPackedBitMask(data_0205fe0c->linkFlags, index) ? TRUE : FALSE)) {
            found = TRUE;
        } else {
            found = IsStopKind(entry);
        }
    } else {
        found = FALSE;
    }
    return found;
}

void MoveMatrixCursorRight_020cb658(MatrixMenu *menu)
{
    GridEntry **cell;
    u16 count;
    GridEntry **rowEnd;
    int width;
    GridMap *map;
    GridEntry *current;
    GridEntry *entry;
    GridEntry *neighbor;
    u8 kind;
    u16 i;
    int index;
    int rowOffset;

    current = NULL;
    width = *menu->map->columnCount;

    if (menu->active == 0 || menu->busy12dc8 != 0 || menu->busy74 != 0 || menu->busy17524 != 0 ||
        menu->busy88 != 0 || menu->busy13ea0 != 0 || menu->busy13e64 != 0 || menu->busy70 != 0) {
        return;
    }
    if (!IsMatrixInputReady_020caa6c(menu) || menu->busy17528 != 0 || GetDialogInputMode_020c42b4(menu)) {
        return;
    }
    rowOffset = menu->cursorY * width * 4;
    cell = (GridEntry **)((u8 *)menu->map->tiles + rowOffset);
    cell += menu->cursorX;
    entry = menu->current;
    kind = entry->kind;
    current = entry;
    count = GetCursorFrame(kind)->height >> 4;
    if (kind != 0 && (kind < 0xe || kind == 0x19)) {
        entry = func_ov075_020cac34(menu, 2);
        if (entry == NULL) {
            if (menu->soundEnabled) {
                PlaySoundEffect_0204d924(1, 0);
            }
            ShowEntryHeaderMessage_020cad14(menu, menu->current);
            ShowNextUnlockNotice_020cc9fc(menu, TRUE, FALSE);
            return;
        }
        if (current != entry) {
            current = entry;
            TracePipePath_020caa98(menu->map, entry, 2, &current);
            goto moved;
        }
    }
    if (menu->cursorX >= 0x2e) {
        return;
    }
    map = menu->map;
    rowEnd = &map->tiles[(menu->cursorY + 1) * width];
    cell++;
    neighbor = *cell;
    if (neighbor != NULL) {
        index = GetEntryIndex(map, neighbor);
        if (index < 0) {
            index = neighbor->linkId;
        }
        if (index >= 0 && index == GetEntryIndex(map, menu->current)) {
            cell++;
        }
        if (TracePipePath_020caa98(map, *cell, 2, &current)) {
            goto moved;
        }
    }
    if (cell >= rowEnd) {
        return;
    }
    do {
        for (i = 0; i < count; i++) {
            entry = cell[i * width];
            if (IsCursorStop(menu->map, entry, current)) {
               current = cell[i * width];
                goto moved;
            }
        }
        cell++;
    } while (cell < rowEnd);
    return;

moved:
    if (menu->soundEnabled) {
        PlaySoundEffect_0204d924(1, 0);
    }
    JumpCursorToEntry_020cae58(menu, current, TRUE);
}
