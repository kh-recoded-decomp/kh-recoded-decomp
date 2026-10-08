#include "nitro/types.h"

typedef struct PaletteData {
    u32 format;
    BOOL isExtended;
    u32 size;
    void *data;
} PaletteData;

typedef struct CharacterData {
    u8 pad_00[0x10];
    u32 size;
    void *data;
} CharacterData;

typedef struct BgGraphicsData {
    void *screen;
    CharacterData *character;
    PaletteData *palette;
} BgGraphicsData;

typedef struct BoardState {
    int resourceA;
    int resourceB;
    void *widget;
    char widgetData[0x28 - 0xc];
    char animSet[0x74 - 0x28];
    char objectSet[0x6558 - 0x74];
    s16 originX;
    s16 originY;
    int markerSlots[4];
    int cellIds[6][3];
    int itemSlots[30];
    int cursorSlot;
    int targetSlot;
    int progressDigits[10];
    int goalDigits[10];
    int scoreDigits[10];
    int moveDigits[10];
    int pad66d4;
    int hintSlot;
    int goalSlot;
    int useChannel;
    int goalShown;
    int menuShown;
    int showTutorial;
    u16 prevTouch[4];
    s8 shownItems[6];
} BoardState;

typedef struct BoardCursor {
    char pad00[0x10];
    s16 score;
    s16 moves;
    char pad14[0x24 - 0x14];
    u8 progress;
    u8 goal;
    char pad26[0x31 - 0x26];
    s8 slotValues[6];
    s8 directions[6];
    s8 links[6][4];
    char pad55;
    s8 items[6];
} BoardCursor;

typedef struct BoardGlobals {
    BoardState *state;
    int ready;
    BoardCursor *cursor;
} BoardGlobals;

typedef struct CellOffset {
    int x;
    int y;
} CellOffset;

typedef struct CellTable {
    int cells[6][3];
} CellTable;

typedef struct LinkEntry {
    int node;
    int linkNode;
    int linkDir;
    int sprite;
} LinkEntry;

typedef struct LinkTable {
    LinkEntry entries[8];
} LinkTable;

typedef struct OffsetTable {
    CellOffset offsets[4];
} OffsetTable;

#define BOARD_VRAM_KEY(base) ((((base) + 0x8000) & 0xfffffc) << 7)

extern BoardGlobals data_ov024_020b7520;
extern int data_ov024_020b752c[6];
extern const CellOffset data_ov024_020b7384[];
extern const CellTable data_ov024_020b73b4;
extern const LinkTable data_ov024_020b73fc;
extern const OffsetTable data_ov024_020b7364;

extern void func_0204f0c0(void *manager, int slot);
extern void ReleaseOverlayResourceSlots_020b5dc0(void);
extern void ClearTileTableRowAndMarkDirty_020b9d18(void *table, int id);
extern void *func_0202c48c(u32 fileId, u32 heap);
extern void GetBgDataFromArchive_0202b554(BgGraphicsData *out, void *archive, int screenIndex, int characterIndex,
                                          int paletteIndex);
extern void GXS_LoadBGPltt_020072b4(void *data, u32 offset, u32 size);
extern void GXS_LoadBG2Char_02007b00(void *data, u32 offset, u32 size);
extern void NNSi_FndFreeFromDefaultHeap_0202a1c4(void *block);
extern void *FindActiveRecordById_020b8184(void *animSet, u16 id);
extern void TagTracker_InvokeCallback_020b8210(void *animSet, void *record);
extern void func_ov027_020b8284(void *animSet, void *record, u8 sequence);
extern int GFXi_EnqueueCommand_02014090(int command, int offset, void *data, int size);
extern void DrawWidgetNumber_020b5de4(void *manager, int widgetId, int layer, int value, int spacing, int *slots, BOOL reset);
extern void func_0204f378(void *manager, int slot, int value);
extern void *FindWidgetById_020b90a4(void *manager, int widgetId);
extern void SetEntrySlotsVisible_020b9580(void *manager, void *widget, int visible);
extern int CreateDefaultObjectSlot_020b6778(void *manager, int animation, int resource, int x, int y);
extern void SetEntryRotation_0204f308(void *manager, int slot, u16 rotation);

void BuildBoardLayout_020b5828(BoardCursor *cursor, int loadBackground)
{
    CellTable cells;
    LinkTable links;
    BgGraphicsData bgData;
    OffsetTable offsets;
    void *archive;
    int node;
    int i;
    int j;
    int sequence;

    data_ov024_020b7520.ready = 0;
    data_ov024_020b7520.state->originX = 0;
    if (cursor->slotValues[2] < 0 && cursor->slotValues[3] < 0) {
        data_ov024_020b7520.state->originX += 0x20;
    }
    if (cursor->slotValues[4] < 0 && cursor->slotValues[5] < 0) {
        data_ov024_020b7520.state->originX += 0x20;
    }
    data_ov024_020b7520.state->originY =
        (cursor->slotValues[1] < 0 && cursor->slotValues[3] < 0 && cursor->slotValues[5] < 0) ? 0x20 : 0;
    *(vu32 *)0x04001018 = ((-data_ov024_020b7520.state->originX) & 0x1ff) |
                          (((-data_ov024_020b7520.state->originY) << 16) & (0x1ff << 16));

    for (i = 0; i < 6; i++) {
        for (j = 0; j < 3; j++) {
            if (data_ov024_020b7520.state->cellIds[i][j] >= 0) {
                func_0204f0c0(data_ov024_020b7520.state->objectSet, data_ov024_020b7520.state->cellIds[i][j]);
            }
            data_ov024_020b7520.state->cellIds[i][j] = -1;
        }
    }
    ReleaseOverlayResourceSlots_020b5dc0();
    ClearTileTableRowAndMarkDirty_020b9d18(data_ov024_020b7520.state->widget, 0x1a);
    ClearTileTableRowAndMarkDirty_020b9d18(data_ov024_020b7520.state->widget, 0x1b);
    if (loadBackground) {
        ClearTileTableRowAndMarkDirty_020b9d18(data_ov024_020b7520.state->widget, 0x18);
        ClearTileTableRowAndMarkDirty_020b9d18(data_ov024_020b7520.state->widget, 0x19);
        archive = func_0202c48c(BOARD_VRAM_KEY(data_ov024_020b7520.state->resourceB) | 0x80000018, 0xe);
        GetBgDataFromArchive_0202b554(&bgData, archive, -1, 0, 0);
        GXS_LoadBGPltt_020072b4(bgData.palette->data, 0, bgData.palette->size);
        GXS_LoadBG2Char_02007b00(bgData.character->data, 0, bgData.character->size);
        NNSi_FndFreeFromDefaultHeap_0202a1c4(archive);
    }
    TagTracker_InvokeCallback_020b8210(data_ov024_020b7520.state->animSet,
                                       FindActiveRecordById_020b8184(data_ov024_020b7520.state->animSet, 1000));
    TagTracker_InvokeCallback_020b8210(data_ov024_020b7520.state->animSet,
                                       FindActiveRecordById_020b8184(data_ov024_020b7520.state->animSet, 1010));

    for (i = 0; i < 6; i++) {
        if (cursor->slotValues[i] >= 0) {
            data_ov024_020b752c[i] = (int)func_0202c48c(
                ((cursor->directions[i] + 0x17 + cursor->slotValues[i] * 4) & 0x1ff) |
                    (BOARD_VRAM_KEY(data_ov024_020b7520.state->resourceA) | 0x80000000),
                0xe);
            GetBgDataFromArchive_0202b554(&bgData, (void *)data_ov024_020b752c[i], -1, 0, 0);
            GFXi_EnqueueCommand_02014090(0x17, i * 0x800 + 0xc00, bgData.character->data, bgData.character->size);
            sequence = 0xe;
            if (cursor->items[i]) {
                sequence = 0xd;
            }
            func_ov027_020b8284(data_ov024_020b7520.state->animSet,
                                FindActiveRecordById_020b8184(data_ov024_020b7520.state->animSet, i + 1001), sequence);
            TagTracker_InvokeCallback_020b8210(data_ov024_020b7520.state->animSet,
                                               FindActiveRecordById_020b8184(data_ov024_020b7520.state->animSet, i + 1001));
        } else {
            data_ov024_020b752c[i] = 0;
        }
        data_ov024_020b7520.state->shownItems[i] = cursor->items[i];
    }

    DrawWidgetNumber_020b5de4(data_ov024_020b7520.state->objectSet, 2, 8, cursor->progress, 0xd,
                              data_ov024_020b7520.state->progressDigits, 1);
    DrawWidgetNumber_020b5de4(data_ov024_020b7520.state->objectSet, 4, 9, cursor->goal, 8,
                              data_ov024_020b7520.state->goalDigits, 1);
    DrawWidgetNumber_020b5de4(data_ov024_020b7520.state->objectSet, 5, 8, cursor->score, 0xd,
                              data_ov024_020b7520.state->scoreDigits, 1);
    DrawWidgetNumber_020b5de4(data_ov024_020b7520.state->objectSet, 7, 9, cursor->moves, 8,
                              data_ov024_020b7520.state->moveDigits, 1);
    func_0204f378(data_ov024_020b7520.state->objectSet, data_ov024_020b7520.state->hintSlot, 0);
    func_0204f378(data_ov024_020b7520.state->objectSet, data_ov024_020b7520.state->goalSlot, 0);
    SetEntrySlotsVisible_020b9580(data_ov024_020b7520.state->objectSet,
                                  FindWidgetById_020b90a4(data_ov024_020b7520.state->objectSet, 8), 0);
    data_ov024_020b7520.state->menuShown = 0;

    cells = data_ov024_020b73b4;
    links = data_ov024_020b73fc;
    offsets = data_ov024_020b7364;
    for (i = 0; i < 6; i++) {
        if (cursor->slotValues[i] >= 0) {
            for (j = 0; j < 3; j++) {
                if (cells.cells[i][j] >= 0 && cursor->links[i][cells.cells[i][j]] >= 0) {
                    data_ov024_020b7520.state->cellIds[i][j] = CreateDefaultObjectSlot_020b6778(
                        data_ov024_020b7520.state->objectSet, 0, cursor->slotValues[i] * 4 + (((cells.cells[i][j] + 4 - cursor->directions[i]) & 3) + 0xb),
                        data_ov024_020b7520.state->originX + (data_ov024_020b7384[i].x + offsets.offsets[cursor->directions[i]].x),
                        data_ov024_020b7520.state->originY + (data_ov024_020b7384[i].y + offsets.offsets[cursor->directions[i]].y));
                    SetEntryRotation_0204f308(data_ov024_020b7520.state->objectSet,
                                              data_ov024_020b7520.state->cellIds[i][j], -(cursor->directions[i] * 0x4000));
                    func_0204f378(data_ov024_020b7520.state->objectSet, data_ov024_020b7520.state->cellIds[i][j], 1);
                }
            }
        }
    }
    for (i = 0; i < 8; i++) {
        node = links.entries[i].node;
        if (cursor->slotValues[node] < 0 && cursor->links[links.entries[i].linkNode][links.entries[i].linkDir] >= 0) {
            data_ov024_020b7520.state->cellIds[node][0] = CreateDefaultObjectSlot_020b6778(
                data_ov024_020b7520.state->objectSet, 0, links.entries[i].sprite + 0x5b,
                data_ov024_020b7520.state->originX + data_ov024_020b7384[node].x,
                data_ov024_020b7520.state->originY + data_ov024_020b7384[node].y);
            func_0204f378(data_ov024_020b7520.state->objectSet, data_ov024_020b7520.state->cellIds[node][0], 1);
        }
    }
    data_ov024_020b7520.state->goalShown = 0;
    data_ov024_020b7520.ready = 1;
}
