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

extern BoardGlobals gBoardScreenGlobals;
extern int gBoardNodeGraphicsBufferStorage[6];
extern const CellOffset gBoardNodeScreenX0[];
extern const CellTable gBoardNodeLinkDirections;
extern const LinkTable gBoardGapConnectorConfigs;
extern const OffsetTable gBoardDirectionScreenOffsets;

extern void UnlinkActiveIndexedRecord(void *manager, int slot);
extern void ReleaseOverlayResourceSlots(void);
extern void ClearTileTableRowAndMarkDirty(void *table, int id);
extern void *LoadFileAllocFromHeapTail(u32 fileId, u32 heap);
extern void GetBgDataFromArchive(BgGraphicsData *out, void *archive, int screenIndex, int characterIndex,
                                          int paletteIndex);
extern void GXS_LoadBGPltt(void *data, u32 offset, u32 size);
extern void GXS_LoadBG2Char(void *data, u32 offset, u32 size);
extern void NNSi_FndFreeFromDefaultHeap(void *block);
extern void *FindActiveRecordById(void *animSet, u16 id);
extern void TagTracker_InvokeCallback(void *animSet, void *record);
extern void StampTileRegionPalette(void *animSet, void *record, u8 sequence);
extern int NNS_GfdRegisterNewVramTransferTask(int command, int offset, void *data, int size);
extern void DrawWidgetNumber(void *manager, int widgetId, int layer, int value, int spacing, int *slots, BOOL reset);
extern void IndexedRecords_SetFlag2(void *manager, int slot, int value);
extern void *FindWidgetById(void *manager, int widgetId);
extern void SetEntrySlotsVisible(void *manager, void *widget, int visible);
extern int CreateDefaultObjectSlot(void *manager, int animation, int resource, int x, int y);
extern void SetEntryRotation(void *manager, int slot, u16 rotation);

void BuildBoardLayout(BoardCursor *cursor, int loadBackground)
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

    gBoardScreenGlobals.ready = 0;
    gBoardScreenGlobals.state->originX = 0;
    if (cursor->slotValues[2] < 0 && cursor->slotValues[3] < 0) {
        gBoardScreenGlobals.state->originX += 0x20;
    }
    if (cursor->slotValues[4] < 0 && cursor->slotValues[5] < 0) {
        gBoardScreenGlobals.state->originX += 0x20;
    }
    gBoardScreenGlobals.state->originY =
        (cursor->slotValues[1] < 0 && cursor->slotValues[3] < 0 && cursor->slotValues[5] < 0) ? 0x20 : 0;
    *(vu32 *)0x04001018 = ((-gBoardScreenGlobals.state->originX) & 0x1ff) |
                          (((-gBoardScreenGlobals.state->originY) << 16) & (0x1ff << 16));

    for (i = 0; i < 6; i++) {
        for (j = 0; j < 3; j++) {
            if (gBoardScreenGlobals.state->cellIds[i][j] >= 0) {
                UnlinkActiveIndexedRecord(gBoardScreenGlobals.state->objectSet, gBoardScreenGlobals.state->cellIds[i][j]);
            }
            gBoardScreenGlobals.state->cellIds[i][j] = -1;
        }
    }
    ReleaseOverlayResourceSlots();
    ClearTileTableRowAndMarkDirty(gBoardScreenGlobals.state->widget, 0x1a);
    ClearTileTableRowAndMarkDirty(gBoardScreenGlobals.state->widget, 0x1b);
    if (loadBackground) {
        ClearTileTableRowAndMarkDirty(gBoardScreenGlobals.state->widget, 0x18);
        ClearTileTableRowAndMarkDirty(gBoardScreenGlobals.state->widget, 0x19);
        archive = LoadFileAllocFromHeapTail(BOARD_VRAM_KEY(gBoardScreenGlobals.state->resourceB) | 0x80000018, 0xe);
        GetBgDataFromArchive(&bgData, archive, -1, 0, 0);
        GXS_LoadBGPltt(bgData.palette->data, 0, bgData.palette->size);
        GXS_LoadBG2Char(bgData.character->data, 0, bgData.character->size);
        NNSi_FndFreeFromDefaultHeap(archive);
    }
    TagTracker_InvokeCallback(gBoardScreenGlobals.state->animSet,
                                       FindActiveRecordById(gBoardScreenGlobals.state->animSet, 1000));
    TagTracker_InvokeCallback(gBoardScreenGlobals.state->animSet,
                                       FindActiveRecordById(gBoardScreenGlobals.state->animSet, 1010));

    for (i = 0; i < 6; i++) {
        if (cursor->slotValues[i] >= 0) {
            gBoardNodeGraphicsBufferStorage[i] = (int)LoadFileAllocFromHeapTail(
                ((cursor->directions[i] + 0x17 + cursor->slotValues[i] * 4) & 0x1ff) |
                    (BOARD_VRAM_KEY(gBoardScreenGlobals.state->resourceA) | 0x80000000),
                0xe);
            GetBgDataFromArchive(&bgData, (void *)gBoardNodeGraphicsBufferStorage[i], -1, 0, 0);
            NNS_GfdRegisterNewVramTransferTask(0x17, i * 0x800 + 0xc00, bgData.character->data, bgData.character->size);
            sequence = 0xe;
            if (cursor->items[i]) {
                sequence = 0xd;
            }
            StampTileRegionPalette(gBoardScreenGlobals.state->animSet,
                                FindActiveRecordById(gBoardScreenGlobals.state->animSet, i + 1001), sequence);
            TagTracker_InvokeCallback(gBoardScreenGlobals.state->animSet,
                                               FindActiveRecordById(gBoardScreenGlobals.state->animSet, i + 1001));
        } else {
            gBoardNodeGraphicsBufferStorage[i] = 0;
        }
        gBoardScreenGlobals.state->shownItems[i] = cursor->items[i];
    }

    DrawWidgetNumber(gBoardScreenGlobals.state->objectSet, 2, 8, cursor->progress, 0xd,
                              gBoardScreenGlobals.state->progressDigits, 1);
    DrawWidgetNumber(gBoardScreenGlobals.state->objectSet, 4, 9, cursor->goal, 8,
                              gBoardScreenGlobals.state->goalDigits, 1);
    DrawWidgetNumber(gBoardScreenGlobals.state->objectSet, 5, 8, cursor->score, 0xd,
                              gBoardScreenGlobals.state->scoreDigits, 1);
    DrawWidgetNumber(gBoardScreenGlobals.state->objectSet, 7, 9, cursor->moves, 8,
                              gBoardScreenGlobals.state->moveDigits, 1);
    IndexedRecords_SetFlag2(gBoardScreenGlobals.state->objectSet, gBoardScreenGlobals.state->hintSlot, 0);
    IndexedRecords_SetFlag2(gBoardScreenGlobals.state->objectSet, gBoardScreenGlobals.state->goalSlot, 0);
    SetEntrySlotsVisible(gBoardScreenGlobals.state->objectSet,
                                  FindWidgetById(gBoardScreenGlobals.state->objectSet, 8), 0);
    gBoardScreenGlobals.state->menuShown = 0;

    cells = gBoardNodeLinkDirections;
    links = gBoardGapConnectorConfigs;
    offsets = gBoardDirectionScreenOffsets;
    for (i = 0; i < 6; i++) {
        if (cursor->slotValues[i] >= 0) {
            for (j = 0; j < 3; j++) {
                if (cells.cells[i][j] >= 0 && cursor->links[i][cells.cells[i][j]] >= 0) {
                    gBoardScreenGlobals.state->cellIds[i][j] = CreateDefaultObjectSlot(
                        gBoardScreenGlobals.state->objectSet, 0, cursor->slotValues[i] * 4 + (((cells.cells[i][j] + 4 - cursor->directions[i]) & 3) + 0xb),
                        gBoardScreenGlobals.state->originX + (gBoardNodeScreenX0[i].x + offsets.offsets[cursor->directions[i]].x),
                        gBoardScreenGlobals.state->originY + (gBoardNodeScreenX0[i].y + offsets.offsets[cursor->directions[i]].y));
                    SetEntryRotation(gBoardScreenGlobals.state->objectSet,
                                              gBoardScreenGlobals.state->cellIds[i][j], -(cursor->directions[i] * 0x4000));
                    IndexedRecords_SetFlag2(gBoardScreenGlobals.state->objectSet, gBoardScreenGlobals.state->cellIds[i][j], 1);
                }
            }
        }
    }
    for (i = 0; i < 8; i++) {
        node = links.entries[i].node;
        if (cursor->slotValues[node] < 0 && cursor->links[links.entries[i].linkNode][links.entries[i].linkDir] >= 0) {
            gBoardScreenGlobals.state->cellIds[node][0] = CreateDefaultObjectSlot(
                gBoardScreenGlobals.state->objectSet, 0, links.entries[i].sprite + 0x5b,
                gBoardScreenGlobals.state->originX + gBoardNodeScreenX0[node].x,
                gBoardScreenGlobals.state->originY + gBoardNodeScreenX0[node].y);
            IndexedRecords_SetFlag2(gBoardScreenGlobals.state->objectSet, gBoardScreenGlobals.state->cellIds[node][0], 1);
        }
    }
    gBoardScreenGlobals.state->goalShown = 0;
    gBoardScreenGlobals.ready = 1;
}
