#pragma opt_dead_assignments off
#include "nitro/types.h"

typedef struct PipeTile {
    u16 cell;
    u8 kind;
    s8 linkId;
    u8 pad_04[0x10];
} PipeTile;

typedef struct PipeBoard {
    u8 pad_0000[0x18];
    PipeTile *linked[(0x98 - 0x18) / 4];
    u8 *width;
    PipeTile *cells[(0x1b9c - 0x9c) / 4];
    u8 pad_1b9c[0x2be8 - 0x1b9c];
    u8 cellLevels[1];
} PipeBoard;

typedef struct SaveData {
    u8 pad_0000[0x2c5c];
    u8 linkFlags[0x2c67 - 0x2c5c];
    u8 level;
} SaveData;

typedef struct KindInfo {
    u8 packed;
    u8 pad_01[3];
} KindInfo;

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
    PipeBoard *map;
    PipeTile *current;
    u8 pad_12dd8[0x13e64 - 0x12dd8];
    u16 busy13e64;
    u8 pad_13e66[0x13ea0 - 0x13e66];
    int busy13ea0;
    u8 pad_13ea4[0x17524 - 0x13ea4];
    int busy17524;
    int busy17528;
} MatrixMenu;

extern SaveData *data_0205fe0c;
extern KindInfo data_ov075_020d1454[];
extern int GetPackedBitMask(void *bits, int index);
extern BOOL PlaySoundEffect_0204d924(int seqArcNo, int index);
extern s32 GetDialogInputMode_020c42b4(MatrixMenu *menu);
extern BOOL IsMatrixInputReady_020caa6c(MatrixMenu *menu);
extern BOOL TracePipePath_020caa98(PipeBoard *board, PipeTile *tile, int dir, PipeTile **out);
extern PipeTile *func_ov075_020cac34(MatrixMenu *menu, int dir);
extern void ShowEntryHeaderMessage_020cad14(MatrixMenu *menu, PipeTile *entry);
extern void JumpCursorToEntry_020cae58(MatrixMenu *menu, PipeTile *entry, BOOL skipCurrent);
extern BOOL ShowNextUnlockNotice_020cc9fc(MatrixMenu *menu, BOOL eventMode, BOOL queryOnly);

static inline int GetEntryIndex(PipeBoard *map, PipeTile *entry, PipeTile *base)
{
    if (entry >= base) {
        return entry - base;
    }
    return -1;
}

static inline int GetKindSlot(int kind)
{
    if (kind < 3 || kind >= 0xe) {
        return 0;
    }
    return kind - 2;
}

static inline BOOL IsPlainKind(u8 kind)
{
    BOOL plain = TRUE;
    u8 bit = kind + 0xfc;

    if (bit <= 0x15 && ((1 << bit) & 0x200003)) {
        plain = FALSE;
    }
    return plain;
}

static inline BOOL CanSelectTile(PipeBoard *board, PipeTile *selected, PipeTile *tile)
{
    int index;
    BOOL ok;
    PipeTile *current = selected;

    if (tile != NULL && current != tile && board->cellLevels[tile->cell] <= data_0205fe0c->level) {
        index = GetEntryIndex(board, tile, board->linked[0]);
        if (index < 0) {
            index = tile->linkId;
        }
        if (index >= 0 && !(GetPackedBitMask(data_0205fe0c->linkFlags, index) ? TRUE : FALSE)) {
            return TRUE;
        }
        ok = FALSE;
        if (IsPlainKind(tile->kind) && tile->kind < 0xe) {
            ok = TRUE;
        }
        return ok;
    }
    return FALSE;
}

void MoveMatrixCursorUp_020caf38(MatrixMenu *menu)
{
    PipeTile *selected = NULL;
    u8 width = *menu->map->width;
    PipeTile **row;
    PipeTile *found;
    PipeTile *cur;
    u16 count;
    PipeTile **start;
    PipeBoard *map;
    int stride;
    u16 i;
    u8 kind;
    int rowOffset;

    if (menu->active == 0 || menu->busy12dc8 != 0 || menu->busy74 != 0 || menu->busy17524 != 0 ||
        menu->busy88 != 0 || menu->busy13ea0 != 0 || menu->busy13e64 != 0 || menu->busy70 != 0) {
        return;
    }
    if (!IsMatrixInputReady_020caa6c(menu) || menu->busy17528 != 0 || GetDialogInputMode_020c42b4(menu) != 0) {
        return;
    }
    rowOffset = menu->cursorY * width * 4;
    row = (PipeTile **)((u8 *)menu->map->cells + rowOffset);
    row += menu->cursorX;
    cur = menu->current;
    kind = cur->kind;
    selected = cur;
    count = data_ov075_020d1454[GetKindSlot(cur->kind)].packed >> 4;
    if (kind != 0 && (kind < 0xe || kind == 0x19)) {
        found = func_ov075_020cac34(menu, 1);
        if (found == NULL) {
            if (menu->soundEnabled) {
                PlaySoundEffect_0204d924(1, 0);
            }
            ShowEntryHeaderMessage_020cad14(menu, menu->current);
            ShowNextUnlockNotice_020cc9fc(menu, TRUE, FALSE);
            return;
        }
        if (selected != found) {
            selected = found;
            TracePipePath_020caa98(menu->map, found, 1, &selected);
            goto jump;
        }
    }
    if (menu->cursorY <= 0) {
        return;
    }
    map = menu->map;
    start = map->cells;
    stride = width;
    row -= stride;
    if (TracePipePath_020caa98(map, *row, 1, &selected)) {
        goto jump;
    }
    do {
        for (i = 0; i < count; i++) {
            if (CanSelectTile(menu->map, selected, row[i])) {
                selected = row[i];
                goto jump;
            }
        }
        row -= stride;
    } while (row >= start);
    return;
jump:
    if (menu->soundEnabled) {
        PlaySoundEffect_0204d924(1, 0);
    }
    JumpCursorToEntry_020cae58(menu, selected, TRUE);
}
