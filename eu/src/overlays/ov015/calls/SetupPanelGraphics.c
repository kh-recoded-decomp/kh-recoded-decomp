#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct {
    u32 counts[5];
} BgContainerConfig;

typedef struct {
    u32 cellFileId;
    u32 unk_04[4];
    u32 animFileId;
} ObjManagerConfig;

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
    u8 pad_00[8];
    u32 size;
    void *rawData;
} PaletteData;

typedef struct {
    void *screen;
    CharacterData *character;
    PaletteData *palette;
} BgGraphicsData;

typedef struct {
    u16 id;
    u16 pad_02;
    u32 unk_04;
    ScreenData *screen;
} BgScreenEntry;

typedef struct {
    u8 pad_00[4];
    s16 charOffset;
} BgScreenRecord;

typedef struct {
    fx32 x;
    fx32 y;
} ElementPosition;

typedef struct {
    u32 words[4];
} ProfileBlock;

typedef struct {
    s8 state;
    s8 unk_01;
    s8 randomDigit;
    s8 randomPick;
    u8 pad_04[0xc2 - 0x04];
    u16 extPaletteColor;
    u16 extPaletteColorCopy;
    u8 pad_C6[0xcc - 0xc6];
    fx32 scaleX;
    fx32 scaleY;
    fx32 offsetX;
    fx32 offsetY;
    u8 pad_DC[0xe0 - 0xdc];
    u8 : 4;
    u8 mainLoaded : 1;
    u8 subLoaded : 1;
    u8 : 2;
    u8 : 3;
    u8 flagE1Bit3 : 1;
    u8 flagE1Bit4 : 1;
    u8 flagE1Mode : 2;
    u8 flagE1Bit7 : 1;
    u8 : 1;
    u8 flagE2Bit1 : 1;
    u8 flagE2Bit2 : 1;
    u8 : 5;
    u8 pad_E3[0x100 - 0xe3];
    fx32 avatarX;
    fx32 avatarY;
    u8 pad_108[0x118 - 0x108];
    ProfileBlock *profile;
    u8 pad_11C[0x5aa - 0x11c];
    u8 avatarAlpha;
    u8 avatarMode : 2;
    u8 : 6;
    u8 mainBg[0x4c];
    u8 subBg[0x4c];
    u8 mainObj[0x647c];
    u8 subObj[0x647c];
    u8 pad_CF3C[0xcf48 - 0xcf3c];
    ProfileBlock profileCopy;
} PanelState;

extern PanelState *data_ov015_0207e960;
extern const BgContainerConfig data_ov015_02079fa0;
extern const BgContainerConfig data_ov015_02079fb4;
extern const ObjManagerConfig data_ov015_0207a004;
extern const ObjManagerConfig data_ov015_0207a01c;
extern u32 gLinkPanelAssetPaths[];
extern u32 data_ov015_0207a19c[];
extern const char sOv015_WxcWlmP2_0207e7e0[];
extern const char sOv015_WxcWlaP2_0207e7ec[];

extern void func_ov015_020724dc(void);
extern void func_ov015_02072754(void);
extern void func_ov015_02072758(void);
extern void func_ov015_02072814(void);
extern void func_ov015_02072830(void);
extern void func_ov015_0207283c(void);
extern void func_ov015_02072848(void);
extern void func_ov015_02072854(void);

extern void func_ov015_0206c660(void);
extern void GX_SetBankForSubOBJExtPltt(int bank);
extern void GX_SetBankForOBJExtPltt(int bank);
extern void func_ov002_020629a8(void);
extern int Msg_OpenContainerAndReadHeader(const char *name, u32 mode, BOOL allocFromEnd);
extern void ZeroHalfThenFree(int handle);
extern void *func_0202c4a0(u32 fileId, u32 type);
extern void NNSi_FndFreeFromDefaultHeap(void *block);
extern void GetBgDataFromArchive(BgGraphicsData *out, void *archive, int screenIndex, int characterIndex,
                                          int paletteIndex);
extern void GX_LoadBGPltt(void *src, u32 offset, u32 size);
extern void GXS_LoadBGPltt(void *src, u32 offset, u32 size);
extern void GX_LoadBG1Char(void *src, u32 offset, u32 size);
extern void GXS_LoadBG1Char(void *src, u32 offset, u32 size);
extern void GX_LoadBG0Scr(void *src, u32 offset, u32 size);
extern void GXS_LoadBG0Scr(void *src, u32 offset, u32 size);
extern void GX_LoadBG1Scr(void *src, u32 offset, u32 size);
extern void GXS_LoadBG1Scr(void *src, u32 offset, u32 size);
extern void GXS_BeginLoadOBJExtPltt(void);
extern void GXS_EndLoadOBJExtPltt(void);
extern u16 func_0202a9e4(u16 range);

extern void func_ov027_020b7d78(void *container, const BgContainerConfig *config);
extern void func_ov027_020b7e44(void *container, u32 fileId);
extern BgScreenEntry *func_ov027_020b8578(void *container, int entryId);
extern BgScreenRecord *FindActiveRecordById(void *container, u32 recordId);
extern int InitializeResourceContainer(void *container, void *config);
extern void InitObjManagerAndMark(void *container, ObjManagerConfig *config);
extern void func_ov027_020b9098(void *container, u32 value);
extern void func_ov027_020b8fb8(void *container, u32 fileId, int count);
extern void SetAllElementObjectModes(void *container, int mode);
extern void *FindWidgetById(void *container, int elementId);
extern void SetEntrySlotsVisible(void *container, void *element, BOOL enabled);
extern void func_ov027_020b97d8(void *container, void *element, int mode);
extern void func_ov027_020b9380(void *container, void *element, ElementPosition *position, int flags);
extern void func_ov027_020b91e8(void *container, void *element, ElementPosition *position, int flags);
extern void func_ov027_020b9604(void *container, void *element);
extern void func_ov027_020b96c0(void *container, void *element, u16 value);
extern void SetFocusedWidget(void *container, void *element);
extern void SetWidgetRootDpadEnabled(void *container, int value);
extern void SetWidgetRootTouchEnabled(void *container, int value);
extern void func_ov027_020b90b8(void *container, void (*callback)(void));
extern void func_ov027_020b90a8(void *container, int elementId, void (*callback)(void));

extern int DispatchContextCommand(int query, int arg1, int arg2, int arg3);
extern int CountSetFlagsInRange(void);
extern ProfileBlock *GetPackedFields(void);
extern void LoadAvatarObjPalette(BOOL useSubScreen);
extern void ResetSelectionView(fx32 *position);
extern void func_ov002_02067c10(void *container, fx32 *position);
extern void SetGroupSlotsVisible(void *container, fx32 *position, int mode);

static inline void SetElementEnabled(void *container, int elementId, BOOL enabled) {
    SetEntrySlotsVisible(container, FindWidgetById(container, elementId), enabled);
}

static inline void SetElementMode(void *container, int elementId, int mode) {
    func_ov027_020b97d8(container, FindWidgetById(container, elementId), mode);
}

static inline void GetElementPosition(void *container, int elementId, ElementPosition *position) {
    func_ov027_020b9380(container, FindWidgetById(container, elementId), position, 0);
}

static inline void SetElementPosition(void *container, int elementId, ElementPosition *position) {
    func_ov027_020b91e8(container, FindWidgetById(container, elementId), position, 0);
}

static inline void ClearElementNumber(void *container, int elementId) {
    func_ov027_020b9604(container, FindWidgetById(container, elementId));
}

static inline void SetElementNumber(void *container, int elementId, u16 value) {
    func_ov027_020b96c0(container, FindWidgetById(container, elementId), value);
}

void SetupPanelGraphics(void) {
    BgContainerConfig mainBgConfig = data_ov015_02079fa0;
    ObjManagerConfig mainObjConfig = data_ov015_0207a004;
    BgContainerConfig subBgConfig = data_ov015_02079fb4;
    ObjManagerConfig subObjConfig = data_ov015_0207a01c;
    BgGraphicsData bgData;
    int handle;
    u32 fileId;
    void *archive;
    BgScreenEntry *entry;
    int level;
    int badgeId;
    int count;
    int tens;
    PanelState *state;

    data_ov015_0207e960->flagE1Bit3 = 0;
    data_ov015_0207e960->flagE2Bit1 = 0;
    data_ov015_0207e960->flagE1Bit4 = 0;
    data_ov015_0207e960->flagE1Bit7 = 0;
    data_ov015_0207e960->flagE1Mode = 0;
    func_ov015_0206c660();
    data_ov015_0207e960->mainLoaded = 1;
    data_ov015_0207e960->subLoaded = 1;
    GX_SetBankForSubOBJExtPltt(0x100);
    GX_SetBankForOBJExtPltt(0);
    *(vu32 *)0x4000000 = (*(vu32 *)0x4000000 & ~0x1f00) | 0x1f00;
    *(vu32 *)0x4001000 = (*(vu32 *)0x4001000 & ~0x1f00) | 0x1e00;
    func_ov002_020629a8();

    handle = Msg_OpenContainerAndReadHeader(sOv015_WxcWlmP2_0207e7e0, 0x10, 0);
    fileId = ((handle + 0x8000) & 0xfffffc) << 7;
    mainObjConfig.cellFileId = fileId | 0x80000002;
    mainObjConfig.animFileId = fileId | 0x80000003;
    func_ov027_020b7d78(data_ov015_0207e960->mainBg, &mainBgConfig);
    func_ov027_020b7e44(data_ov015_0207e960->mainBg, fileId | 0x80000000);
    archive = func_0202c4a0(fileId | 0x80000001, 0x10);
    GetBgDataFromArchive(&bgData, archive, -1, 0, 0);
    GX_LoadBGPltt(bgData.palette->rawData, 0, bgData.palette->size);
    GX_LoadBG1Char(bgData.character->rawData, 0, bgData.character->size);
    entry = func_ov027_020b8578(data_ov015_0207e960->mainBg, 0);
    GX_LoadBG1Scr(entry->screen->rawData, 0, entry->screen->size);
    entry = func_ov027_020b8578(data_ov015_0207e960->mainBg, 1);
    GX_LoadBG0Scr(entry->screen->rawData,
                           FindActiveRecordById(data_ov015_0207e960->mainBg, 1)->charOffset << 6,
                           entry->screen->size);
    InitializeResourceContainer(data_ov015_0207e960->mainObj, NULL);
    InitObjManagerAndMark(data_ov015_0207e960->mainObj, &mainObjConfig);
    func_ov027_020b9098(data_ov015_0207e960->mainObj, gLinkPanelAssetPaths[1]);
    func_ov027_020b8fb8(data_ov015_0207e960->mainObj, mainObjConfig.animFileId, 0x14);
    SetAllElementObjectModes(data_ov015_0207e960->mainObj, 3);
    SetElementEnabled(data_ov015_0207e960->mainObj, 4, 0);
    SetElementEnabled(data_ov015_0207e960->mainObj, 5, 0);
    SetElementEnabled(data_ov015_0207e960->mainObj, 6, 0);
    SetElementEnabled(data_ov015_0207e960->mainObj, 7, 0);
    SetElementEnabled(data_ov015_0207e960->mainObj, 8, 0);
    SetElementEnabled(data_ov015_0207e960->mainObj, 9, 0);
    SetElementEnabled(data_ov015_0207e960->mainObj, 10, 0);
    SetElementEnabled(data_ov015_0207e960->mainObj, 11, 0);
    SetElementEnabled(data_ov015_0207e960->mainObj, 12, 0);
    SetElementEnabled(data_ov015_0207e960->mainObj, 13, 0);
    SetElementEnabled(data_ov015_0207e960->mainObj, 14, 0);
    SetElementEnabled(data_ov015_0207e960->mainObj, 15, 0);
    SetElementEnabled(data_ov015_0207e960->mainObj, 16, 0);
    SetElementEnabled(data_ov015_0207e960->mainObj, 17, 0);
    SetElementEnabled(data_ov015_0207e960->mainObj, 18, 0);
    NNSi_FndFreeFromDefaultHeap(archive);
    ZeroHalfThenFree(handle);

    handle = Msg_OpenContainerAndReadHeader(sOv015_WxcWlaP2_0207e7ec, 0x10, 0);
    func_ov027_020b7d78(data_ov015_0207e960->subBg, &subBgConfig);
    fileId = ((handle + 0x8000) & 0xfffffc) << 7;
    func_ov027_020b7e44(data_ov015_0207e960->subBg, fileId | 0x80000000);
    archive = func_0202c4a0(fileId | 0x80000002, 0x10);
    GetBgDataFromArchive(&bgData, archive, -1, 0, 0);
    GXS_LoadBGPltt(bgData.palette->rawData, 0, bgData.palette->size);
    GXS_LoadBG1Char(bgData.character->rawData, 0, bgData.character->size);
    entry = func_ov027_020b8578(data_ov015_0207e960->subBg, 0);
    GXS_LoadBG1Scr(entry->screen->rawData, 0, entry->screen->size);
    entry = func_ov027_020b8578(data_ov015_0207e960->subBg, 2);
    GXS_LoadBG0Scr(entry->screen->rawData,
                            FindActiveRecordById(data_ov015_0207e960->subBg, 2)->charOffset << 6,
                            entry->screen->size);
    subObjConfig.cellFileId = fileId | 0x80000004;
    subObjConfig.animFileId = fileId | 0x80000007;
    InitializeResourceContainer(data_ov015_0207e960->subObj, NULL);
    InitObjManagerAndMark(data_ov015_0207e960->subObj, &subObjConfig);
    func_ov027_020b9098(data_ov015_0207e960->subObj, gLinkPanelAssetPaths[3]);
    func_ov027_020b8fb8(data_ov015_0207e960->subObj, subObjConfig.animFileId, 0x19);
    SetAllElementObjectModes(data_ov015_0207e960->subObj, 3);
    if (DispatchContextCommand(5, 0, 0, 0) != 0) {
        SetElementEnabled(data_ov015_0207e960->subObj, 8, 1);
        SetElementMode(data_ov015_0207e960->subObj, 8, 0);
    }

    level = DispatchContextCommand(8, 0, 0, 0);
    if (DispatchContextCommand(5, 0, 0, 0) != 0) {
        level = 0;
    }
    if (level >= 80) {
        ElementPosition position;
        void *container;
        container = data_ov015_0207e960->subObj;
        SetEntrySlotsVisible(container, FindWidgetById(container, 14), 1);
        container = data_ov015_0207e960->subObj;
        func_ov027_020b9380(container, FindWidgetById(container, 14), &position, 0);
        *(volatile fx32 *)&position.x = ((position.x >> 12) - 10) << 12;
        container = (*(PanelState *volatile *)&data_ov015_0207e960)->subObj;
        func_ov027_020b91e8(container, FindWidgetById(container, 14), &position, 0);
    } else if (level >= 50) {
        ElementPosition position;
        void *container;
        container = data_ov015_0207e960->subObj;
        SetEntrySlotsVisible(container, FindWidgetById(container, 13), 1);
        container = data_ov015_0207e960->subObj;
        func_ov027_020b9380(container, FindWidgetById(container, 13), &position, 0);
        *(volatile fx32 *)&position.x = ((position.x >> 12) - 10) << 12;
        container = (*(PanelState *volatile *)&data_ov015_0207e960)->subObj;
        func_ov027_020b91e8(container, FindWidgetById(container, 13), &position, 0);
    }
    {
        ElementPosition position;
        GetElementPosition(data_ov015_0207e960->subObj, 10, &position);
        position.x -= 0x19000;
        SetElementPosition(data_ov015_0207e960->subObj, 11, &position);
    }

    LoadAvatarObjPalette(TRUE);
    state = data_ov015_0207e960;
    state->profileCopy = *GetPackedFields();
    state->profile = &state->profileCopy;
    ResetSelectionView(&data_ov015_0207e960->avatarX);
    data_ov015_0207e960->avatarAlpha = 200;
    data_ov015_0207e960->avatarMode = 3;
    data_ov015_0207e960->avatarX = 0xc6000;
    data_ov015_0207e960->avatarY = 0x29000;
    func_ov002_02067c10(data_ov015_0207e960->subObj, &data_ov015_0207e960->avatarX);
    SetGroupSlotsVisible(data_ov015_0207e960->subObj, &data_ov015_0207e960->avatarX, 1);
    SetWidgetRootDpadEnabled(data_ov015_0207e960->subObj, 1);
    SetWidgetRootTouchEnabled(data_ov015_0207e960->subObj, 1);
    SetElementEnabled(data_ov015_0207e960->subObj, 2, 0);
    SetElementEnabled(data_ov015_0207e960->subObj, 3, 0);
    SetElementEnabled(data_ov015_0207e960->subObj, 9, 1);
    SetElementEnabled(data_ov015_0207e960->subObj, 4, 1);
    SetElementEnabled(data_ov015_0207e960->subObj, 17, 1);
    SetElementMode(data_ov015_0207e960->subObj, 4, 3);
    SetElementEnabled(data_ov015_0207e960->subObj, 30, 1);
    SetElementEnabled(data_ov015_0207e960->subObj, 31, 1);
    SetElementEnabled(data_ov015_0207e960->subObj, 32, 1);
    SetElementEnabled(data_ov015_0207e960->subObj, 33, 1);
    SetElementEnabled(data_ov015_0207e960->subObj, 18, 1);

    count = CountSetFlagsInRange();
    ClearElementNumber(data_ov015_0207e960->subObj, 20);
    ClearElementNumber(data_ov015_0207e960->subObj, 21);
    SetElementNumber(data_ov015_0207e960->subObj, 20, count % 10);
    tens = (count / 10) % 10;
    if (tens != 0) {
        SetElementNumber(data_ov015_0207e960->subObj, 21, tens);
    } else {
        SetElementEnabled(data_ov015_0207e960->subObj, 21, 0);
    }

    data_ov015_0207e960->randomDigit = func_0202a9e4(6);
    ClearElementNumber(data_ov015_0207e960->subObj, 10);
    {
        PanelState *panel = data_ov015_0207e960;
        void *container = panel->subObj;
        func_ov027_020b96c0(container, FindWidgetById(container, 10), panel->randomDigit);
    }
    data_ov015_0207e960->randomPick = func_0202a9e4(data_ov015_0207a19c[DispatchContextCommand(6, 0, 0, 0)]);
    {
        void *element = FindWidgetById(data_ov015_0207e960->subObj, 10);
        SetFocusedWidget(data_ov015_0207e960->subObj, element);
    }
    func_ov027_020b90b8(data_ov015_0207e960->subObj, func_ov015_020724dc);
    func_ov027_020b90a8(data_ov015_0207e960->subObj, 4, func_ov015_02072754);
    func_ov027_020b90a8(data_ov015_0207e960->subObj, 9, func_ov015_02072758);
    func_ov027_020b90a8(data_ov015_0207e960->subObj, 17, func_ov015_02072814);
    func_ov027_020b90a8(data_ov015_0207e960->subObj, 30, func_ov015_02072830);
    func_ov027_020b90a8(data_ov015_0207e960->subObj, 31, func_ov015_0207283c);
    func_ov027_020b90a8(data_ov015_0207e960->subObj, 32, func_ov015_02072848);
    func_ov027_020b90a8(data_ov015_0207e960->subObj, 33, func_ov015_02072854);
    NNSi_FndFreeFromDefaultHeap(archive);
    ZeroHalfThenFree(handle);

    data_ov015_0207e960->flagE1Bit3 = 1;
    data_ov015_0207e960->flagE2Bit1 = 1;
    data_ov015_0207e960->flagE2Bit2 = 1;
    data_ov015_0207e960->flagE1Bit4 = 1;
    if (DispatchContextCommand(5, 0, 0, 0) != 0) {
        data_ov015_0207e960->flagE1Mode = 1;
    }
    data_ov015_0207e960->scaleX = func_0202a9e4(0x1000) + 0x1000;
    data_ov015_0207e960->offsetX = func_0202a9e4(0);
    data_ov015_0207e960->scaleY = func_0202a9e4(0x1000) + 0x1000;
    data_ov015_0207e960->offsetY = (func_0202a9e4(0) + 0x80) << 12;
    GXS_BeginLoadOBJExtPltt();
    data_ov015_0207e960->extPaletteColor = *(u16 *)0x068a0002;
    data_ov015_0207e960->extPaletteColorCopy = data_ov015_0207e960->extPaletteColor;
    GXS_EndLoadOBJExtPltt();
}
