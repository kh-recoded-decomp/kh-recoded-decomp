#include "nitro/types.h"

typedef struct {
    s16 x;
    s16 y;
} PanelPoint;

typedef struct {
    int x;
    int y;
} ScenePos;

typedef struct {
    s8 slotX;
    s8 priority;
    u8 pad_02[2];
} SlotStyle;

typedef struct {
    s8 bgIndex;
    s8 charIndex;
    u8 pad_02[23];
} ThemeEntry;

typedef struct {
    u32 cellFileId;
    u32 unk_04[3];
    int count;
    u32 animFileId;
} ObjManagerConfig;

typedef struct {
    u16 x;
    u16 y;
    u16 width;
    u16 height;
    u16 tileBase;
    u16 unk_0a;
    u16 unk_0c;
    u16 palette;
} TileLayout;

typedef struct {
    u8 pad_00[8];
    u32 size;
    u8 rawData[4];
} ScreenData;

typedef struct {
    u8 pad_00[0x10];
    u32 size;
    void *rawData;
} CharacterData;

typedef struct {
    u8 pad_00[0xc];
    void *rawData;
} PaletteData;

typedef struct {
    ScreenData *screen;
    CharacterData *character;
    PaletteData *palette;
} BgGraphicsData;

typedef struct {
    s16 level;
    u16 flags;
    s16 styleId;
    u16 sequence;
    u8 pad_08[4];
    int markSlot;
    int animSlot;
    u8 pad_14[4];
} PanelEntry;

typedef struct {
    u8 pad_0000[0x50];
    s8 theme;
    u8 pad_0051;
    s8 resultKind;
    u8 pad_0053[2];
    s8 entryCount;
    u8 pad_0056;
    s8 total;
    u8 pad_0058[2];
    s8 cleared;
    u8 pad_005b[0x84 - 0x5b];
    PanelEntry entries[9];
    u8 pad_015c[4];
    u8 container[0x65dc - 0x160];
    u8 *records;
    u8 textView[0xc];
    void *headerText;
    void *bodyText;
    u8 pad_65f4[4];
    u8 tileGrid[0xbd38 - 0x65f8];
    u8 mask[1];
} PanelWork;

#define ARCHIVE_FILE_ID(handle, index) (((((handle) + 0x8000) & 0xfffffc) << 7) | 0x80000000 | (index))

extern PanelWork *data_ov015_020812e0;
extern const char data_ov015_0207e8ac[];
extern const char data_ov015_0207e8b8[];
extern const char data_ov015_0207e8c8[];
extern const ObjManagerConfig data_ov015_0207a2e0;
extern const ThemeEntry data_ov015_0207a312[];
extern PanelPoint *data_ov015_0207e884[];
extern const SlotStyle data_ov015_0207a40c[];

extern void func_01ff86fc(u32 data, void *dst, u32 size);
extern void func_01ff89a8(const void *src, void *dst, u32 size);
extern u32 func_0200672c(u32 enabled);
extern void GX_SetBankForSubBGExtPltt_02008ba4(int bank);
extern void GX_SetBankForSubOBJExtPltt_02008c24(int bank);
extern int Msg_OpenContainerAndReadHeader_0202cc6c(const char *name, u32 mode, BOOL allocFromEnd);
extern void ZeroHalfThenFree_0202cd78(int handle);
extern void *func_0202c48c(u32 fileId, u32 heapId);
extern void NNSi_FndFreeFromDefaultHeap_0202a1c4(void *block);
extern void GetBgDataFromArchive_0202b554(BgGraphicsData *out, void *archive, int screenIndex, int characterIndex,
                                          int paletteIndex);
extern void GXS_LoadBGPltt_020072b4(void *src, u32 offset, u32 size);
extern void GXS_LoadBG1Char_02007a20(void *src, u32 offset, u32 size);
extern void GXS_LoadBG0Char_02007940(void *src, u32 offset, u32 size);
extern void GXS_LoadBG0Scr_020075c0(void *src, u32 offset, u32 size);
extern void GXS_LoadBG1Scr_020076a0(void *src, u32 offset, u32 size);
extern void GXS_BeginLoadBGExtPltt_02007e84(void);
extern void GXS_LoadBGExtPltt_02007e9c(void *src, u32 offset, u32 size);
extern void GXS_EndLoadBGExtPltt_02007f04(void);
extern void *G2S_GetBG1ScrPtr_02006e68(void);
extern void *G2S_GetBG3ScrPtr_02007004(void);
extern void *G2S_GetBG0CharPtr_020070ac(void);
extern void *G2S_GetBG1CharPtr_02007100(void);
extern void CopyClippedScreenRegion_020167d0(void *dst, ScreenData *screen, int srcX, int srcY, int dstX, int dstY,
                                             int dstW, int dstH, int width, int height);
extern void func_0204f00c(u8 *records, u32 fileId);
extern int func_0204f0b4(u8 *records, int x, int y);
extern void func_0204f178(u8 *records, int slot, int scale);
extern void Slot_SetMode2Bit_0204f480(u8 *records, int slot, int value);
extern int *SlotTable_SetEntryPriority_0204f468(u8 *records, int slot, int priority);

extern int InitializeResourceContainer_020b8bd4(void *container, void *config);
extern void InitObjManagerAndMark_020b9060(void *container, ObjManagerConfig *config);
extern void func_ov027_020b9078(void *container, u32 fileId);
extern void func_ov027_020b8f98(void *container, u32 fileId, int count);
extern void SetAllElementObjectModes_020b97fc(void *container, int mode);
extern void *func_ov027_020b90a4(void *container, int elementId);
extern void SetEntrySlotsVisible_020b9580(void *container, void *element, int visible);
extern void func_ov027_020b97b8(void *container, void *element, int mode);
extern void func_ov027_020b95e4(void *container, void *element);
extern void func_ov027_020b96a0(void *container, void *element, int value);
extern void func_ov027_020b9874(void *container, int enabled);
extern void func_ov027_020b984c(void *container, int enabled);
extern void LoadPackedFileView_020ba25c(void *view, const char *name, BOOL fromTail);
extern void *func_ov002_02061948(void);

extern void SetContainerSubitem1Active_02078228(BOOL active);
extern void SetSceneRecordValue_020785f8(int slot, ScenePos *pos);
extern void SetPanelEntrySequence_02078638(int index, u32 sequence);
extern u16 BuildTileGridMap_02078e88(void *map, u16 tile);
extern void CopyTileGridToScreen_02078b24(void *dst);
extern void ClearBuffer5100_02078bb4(u8 *buffer);
extern void DrawSlotTileBlocks_02078bd0(u8 *dst, int count, int only, int fill, BOOL blit);
extern void *CreateTileObject_02079c54(u32 ownerId, u32 value, TileLayout *layout, void *tileData, void *mapData);

void SetupPanelBoard_020759cc(void) {
    BgGraphicsData bgA;
    BgGraphicsData bgB;
    u32 handleA;
    BOOL i;
    BOOL priority;
    s32 count;
    void *archiveA;
    void *themeArchive;
    ScenePos pos;
    PanelWork *work;
    PanelPoint *points;
    void *paletteArchive;
    int handleB;
    u16 kind;
    void *archiveB;
    ObjManagerConfig config;
    TileLayout layout;

    i = 0;
    func_01ff86fc(0, (void *)0x6200000, 0x20000);
    func_01ff86fc(0, (void *)0x6600000, 0x20000);
    func_0200672c(0);
    GX_SetBankForSubBGExtPltt_02008ba4(0x80);
    GX_SetBankForSubOBJExtPltt_02008c24(0x100);
    *(vu32 *)0x04001000 = (*(vu32 *)0x04001000 & 0xffcfffef) | 0x10 | 0x200000;
    *(vu16 *)0x04001008 = (*(vu16 *)0x04001008 & 0x43) | 0x388;
    *(vu16 *)0x0400100a = (*(vu16 *)0x0400100a & 0x43) | 0x100;
    *(vu16 *)0x0400100c = (*(vu16 *)0x0400100c & 0x43);
    *(vu16 *)0x0400100e = (*(vu16 *)0x0400100e & 0x43) | 0x294;
    *(vu32 *)0x04001010 = 0;
    *(vu32 *)0x04001014 = 0;
    *(vu32 *)0x04001018 = 0;
    *(vu32 *)0x0400101c = 0;
    *(vu16 *)0x04001008 = (*(vu16 *)0x04001008 & ~3) | 3;
    *(vu16 *)0x0400100a = (*(vu16 *)0x0400100a & ~3) | 2;
    *(vu16 *)0x0400100e = (*(vu16 *)0x0400100e & ~3) | 1;
    *(vu16 *)0x0400100c = (*(vu16 *)0x0400100c & ~3);

    handleA = Msg_OpenContainerAndReadHeader_0202cc6c(data_ov015_0207e8ac, 0x10, 0);
    handleB = Msg_OpenContainerAndReadHeader_0202cc6c(data_ov015_0207e8b8, 0x10, 0);
    GXS_BeginLoadBGExtPltt_02007e84();
    config = data_ov015_0207a2e0;
    config.cellFileId = ARCHIVE_FILE_ID(handleA, 0x0d);
    config.animFileId = ARCHIVE_FILE_ID(handleA, 0x10);
    InitializeResourceContainer_020b8bd4(data_ov015_020812e0->container, NULL);
    InitObjManagerAndMark_020b9060(data_ov015_020812e0->container, &config);
    func_ov027_020b9078(data_ov015_020812e0->container, ARCHIVE_FILE_ID(handleB, 0x0b));
    func_ov027_020b8f98(data_ov015_020812e0->container, config.animFileId, config.count);
    data_ov015_020812e0->records = data_ov015_020812e0->container;
    SetAllElementObjectModes_020b97fc(data_ov015_020812e0->container, 1);
    func_ov027_020b97b8(data_ov015_020812e0->container, func_ov027_020b90a4(data_ov015_020812e0->container, 0x10), 0);
    func_ov027_020b97b8(data_ov015_020812e0->container, func_ov027_020b90a4(data_ov015_020812e0->container, 0x11), 0);
    SetEntrySlotsVisible_020b9580(data_ov015_020812e0->container, func_ov027_020b90a4(data_ov015_020812e0->container, 0), 0);
    func_ov027_020b95e4(data_ov015_020812e0->container, func_ov027_020b90a4(data_ov015_020812e0->container, 2));
    work = data_ov015_020812e0;
    func_ov027_020b96a0(data_ov015_020812e0->container, func_ov027_020b90a4(work->container, 2), work->total);
    func_ov027_020b95e4(data_ov015_020812e0->container, func_ov027_020b90a4(data_ov015_020812e0->container, 4));
    work = data_ov015_020812e0;
    func_ov027_020b96a0(data_ov015_020812e0->container, func_ov027_020b90a4(work->container, 4),
                        (u16)(work->total - work->cleared));
    func_ov027_020b9874(data_ov015_020812e0->container, 1);
    func_ov027_020b984c(data_ov015_020812e0->container, 1);
    SetContainerSubitem1Active_02078228(0);
    *(int *)(data_ov015_020812e0->records + 0x601c) = 0;
    func_0204f00c(data_ov015_020812e0->records, ARCHIVE_FILE_ID(handleA, 0x0e));
    func_0204f00c(data_ov015_020812e0->records, ARCHIVE_FILE_ID(handleA, 0x0f));
    func_0204f00c(data_ov015_020812e0->records, ARCHIVE_FILE_ID(handleA, data_ov015_0207a312[data_ov015_020812e0->theme].bgIndex & 0x1ff));

    count = data_ov015_020812e0->entryCount;
    points = data_ov015_0207e884[count];
    for (; i < count; i++) {
        pos.x = points[i].x << 12;
        pos.y = points[i].y << 12;
        data_ov015_020812e0->entries[i].animSlot = func_0204f0b4(data_ov015_020812e0->records, 0, 0);
        SetPanelEntrySequence_02078638(i, 8);
        func_0204f178(data_ov015_020812e0->records, data_ov015_020812e0->entries[i].animSlot, 0x66);
        Slot_SetMode2Bit_0204f480(data_ov015_020812e0->records, data_ov015_020812e0->entries[i].animSlot, 1);
        SlotTable_SetEntryPriority_0204f468(data_ov015_020812e0->records, data_ov015_020812e0->entries[i].animSlot, 0);
        SetSceneRecordValue_020785f8(data_ov015_020812e0->entries[i].animSlot, &pos);
        priority = data_ov015_0207a40c[data_ov015_020812e0->entries[i].styleId].priority;
        data_ov015_020812e0->entries[i].markSlot =
            func_0204f0b4(data_ov015_020812e0->records, data_ov015_0207a40c[data_ov015_020812e0->entries[i].styleId].slotX,
                          priority);
        func_0204f178(data_ov015_020812e0->records, data_ov015_020812e0->entries[i].markSlot, 0x67);
        Slot_SetMode2Bit_0204f480(data_ov015_020812e0->records, data_ov015_020812e0->entries[i].markSlot, 2);
        SlotTable_SetEntryPriority_0204f468(data_ov015_020812e0->records, data_ov015_020812e0->entries[i].markSlot,
                                            priority);
        SetSceneRecordValue_020785f8(data_ov015_020812e0->entries[i].markSlot, &pos);
    }

    archiveA = func_0202c48c(ARCHIVE_FILE_ID(handleA, 0), 0x10);
    archiveB = func_0202c48c(ARCHIVE_FILE_ID(handleB, 0x0a), 0x10);
    GetBgDataFromArchive_0202b554(&bgA, archiveA, 0, -1, -1);
    GetBgDataFromArchive_0202b554(&bgB, archiveB, -1, 0, 0);
    GXS_LoadBGPltt_020072b4(bgB.palette->rawData, 0, 0x200);
    GXS_LoadBG1Char_02007a20(bgB.character->rawData, 0x2000, bgB.character->size);
    GXS_LoadBG1Scr_020076a0(bgA.screen->rawData, 0, bgA.screen->size);
    kind = data_ov015_020812e0->resultKind;
    if (kind == 5) {
        GetBgDataFromArchive_0202b554(&bgA, archiveA, 1, -1, -1);
        CopyClippedScreenRegion_020167d0(G2S_GetBG1ScrPtr_02006e68(), bgA.screen, 0, 0, 0x12, 0x12, 0x20, 0x20, 0xe, 6);
    } else if (kind == 6) {
        GetBgDataFromArchive_0202b554(&bgA, archiveA, 2, -1, -1);
        CopyClippedScreenRegion_020167d0(G2S_GetBG1ScrPtr_02006e68(), bgA.screen, 0, 0, 0x12, 0x12, 0x20, 0x20, 0xe, 6);
    }
    GetBgDataFromArchive_0202b554(&bgA, archiveA, 3, -1, -1);
    GXS_LoadBG0Scr_020075c0(bgA.screen->rawData, 0, bgA.screen->size);
    if (archiveA != NULL) {
        NNSi_FndFreeFromDefaultHeap_0202a1c4(archiveA);
    }
    if (archiveB != NULL) {
        NNSi_FndFreeFromDefaultHeap_0202a1c4(archiveB);
    }

    themeArchive = func_0202c48c(ARCHIVE_FILE_ID(handleB, data_ov015_0207a312[data_ov015_020812e0->theme].charIndex & 0x1ff),
                             0x10);
    GetBgDataFromArchive_0202b554(&bgA, themeArchive, 0, 0, 0);
    GXS_LoadBGExtPltt_02007e9c(bgA.palette->rawData, 0, 0x200);
    GXS_LoadBG0Char_02007940(bgA.character->rawData, 0, bgA.character->size);
    paletteArchive = func_0202c48c(ARCHIVE_FILE_ID(handleA, 0x02), 0x10);
    GetBgDataFromArchive_0202b554(&bgB, paletteArchive, -1, 0, 0);
    GXS_LoadBGExtPltt_02007e9c(bgB.palette->rawData, 0x6000, 0x200);
    GXS_LoadBGExtPltt_02007e9c(bgA.palette->rawData, 0x6000, 0x1e0);
    GXS_LoadBGExtPltt_02007e9c(bgB.palette->rawData, 0x4000, 0x200);
    GXS_LoadBGExtPltt_02007e9c(bgA.palette->rawData, 0x4000, 0x1e0);
    BuildTileGridMap_02078e88(G2S_GetBG3ScrPtr_02007004(), 1);
    func_01ff89a8(bgB.character->rawData, data_ov015_020812e0->tileGrid, 0x640);
    CopyTileGridToScreen_02078b24(G2S_GetBG0CharPtr_020070ac());
    if (themeArchive != NULL) {
        NNSi_FndFreeFromDefaultHeap_0202a1c4(themeArchive);
    }
    if (paletteArchive != NULL) {
        NNSi_FndFreeFromDefaultHeap_0202a1c4(paletteArchive);
    }
    GXS_EndLoadBGExtPltt_02007f04();
    ZeroHalfThenFree_0202cd78(handleA);
    ZeroHalfThenFree_0202cd78(handleB);

    ClearBuffer5100_02078bb4(data_ov015_020812e0->mask);
    DrawSlotTileBlocks_02078bd0(data_ov015_020812e0->mask, data_ov015_020812e0->entryCount, -1, -1, 1);
    *(vu32 *)0x04001000 = (*(vu32 *)0x04001000 & ~0x1f00) | 0x1f00;
    LoadPackedFileView_020ba25c(data_ov015_020812e0->textView, data_ov015_0207e8c8, 1);

    layout.x = 0x13;
    layout.y = 0xe;
    layout.width = 0xd;
    layout.height = 3;
    layout.unk_0a = 0;
    layout.unk_0c = 0;
    layout.tileBase = 0x3d8;
    layout.palette = 2;
    data_ov015_020812e0->headerText = CreateTileObject_02079c54(5, (u32)func_ov002_02061948(), &layout,
                                                                G2S_GetBG1CharPtr_02007100(), G2S_GetBG1ScrPtr_02006e68());
    layout.x = 0x13;
    layout.unk_0a = 0;
    layout.y = 0x14;
    layout.tileBase = 0x3b1;
    layout.unk_0c = 0;
    layout.width = 0xd;
    layout.height = 3;
    layout.palette = 2;
    data_ov015_020812e0->bodyText = CreateTileObject_02079c54(5, (u32)func_ov002_02061948(), &layout,
                                                              G2S_GetBG1CharPtr_02007100(), G2S_GetBG1ScrPtr_02006e68());
}
