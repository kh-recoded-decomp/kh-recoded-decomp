#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct BgContainerConfig {
    u32 values[5];
} BgContainerConfig;

typedef struct ObjManagerConfig {
    u32 cellResourceId;
    u32 pad_04[4];
    u32 animResourceId;
} ObjManagerConfig;

typedef struct AvatarInfo {
    u32 words[4];
} AvatarInfo;

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

typedef struct ScreenData {
    u8 pad_00[8];
    u32 size;
    u8 data[4];
} ScreenData;

typedef struct BgEntry {
    u8 pad_00[8];
    ScreenData *screen;
} BgEntry;

typedef struct BgRecord {
    u8 pad_00[4];
    s16 offset;
} BgRecord;

typedef struct ObjElement {
    u8 pad_00[0x14];
    s32 animIndex;
} ObjElement;

typedef struct ScreenFlagsE0 {
    u8 pad0_3 : 4;
    u8 subObjReady : 1;
    u8 mainObjReady : 1;
    u8 pad6_7 : 2;
} ScreenFlagsE0;

typedef struct ScreenFlagsE1 {
    u8 slotCleared : 3;
    u8 active : 1;
    u8 scrolling : 1;
    u8 mode : 2;
    u8 visible : 1;
} ScreenFlagsE1;

typedef struct ScreenFlagsE2 {
    u8 pad0 : 1;
    u8 ready : 1;
    u8 busy : 1;
    u8 pad3_7 : 5;
} ScreenFlagsE2;

typedef struct AvatarFlags {
    u8 layer : 2;
    u8 pad2_7 : 6;
} AvatarFlags;

typedef struct PanelContext {
    s8 state;
    s8 nextState;
    s8 level;
    u8 pad_03[0xcc - 0x3];
    s32 scrollMainX;
    s32 scrollSubX;
    s32 scrollMainY;
    s32 scrollSubY;
    u8 pad_dc[0xe0 - 0xdc];
    ScreenFlagsE0 flagsE0;
    ScreenFlagsE1 flagsE1;
    ScreenFlagsE2 flagsE2;
    u8 pad_e3[0x100 - 0xe3];
    VecFx32 avatarPos;
    u8 pad_10c[0x118 - 0x10c];
    AvatarInfo *avatarInfo;
    u8 pad_11c[0x5aa - 0x11c];
    u8 avatarAlpha;
    AvatarFlags avatarFlags;
    u8 bgMain[0x4c];
    u8 bgSub[0x4c];
    u8 objMain[0x647c];
    u8 objSub[0x647c];
    u8 pad_cf3c[0xcf48 - 0xcf3c];
    AvatarInfo avatarInfoCopy;
    u8 pad_cf58[0xdeac - 0xcf58];
    fx32 slotY[3];
} PanelContext;

extern PanelContext *data_ov015_0207e960;
extern const BgContainerConfig data_ov015_02079fc8;
extern const ObjManagerConfig data_ov015_0207a034;
extern const BgContainerConfig data_ov015_02079fdc;
extern const ObjManagerConfig data_ov015_0207a04c;
extern char data_ov015_0207e7ec[];
extern char data_ov015_0207e7f8[];
extern u32 data_ov015_0207e720[];

extern void func_ov015_0206c660(void);
extern void GX_SetBankForSubOBJExtPltt_02008c24(int bank);
extern void GX_SetBankForOBJExtPltt_02008784(int bank);
extern void func_ov002_020629a8(void);
extern void func_ov002_02062768(int value);
extern void *G2S_GetBG0ScrPtr_02006e14(void);
extern void *G2S_GetBG1ScrPtr_02006e68(void);
extern void *G2S_GetBG2ScrPtr_02006f0c(void);
extern void func_01ff8684(u32 value, void *dest, u32 size);
extern int func_0202cc6c(const char *path, u32 kind, u32 fromTop);
extern void func_ov027_020b7d58(void *container, BgContainerConfig *config);
extern void func_ov027_020b7e24(void *container, u32 resourceId);
extern void *func_0202c48c(u32 resourceId, u32 kind);
extern void GetBgDataFromArchive_0202b554(BgGraphicsData *out, void *archive, int screenIndex, int characterIndex,
                                          int paletteIndex);
extern void func_02007250(void *data, u32 offset, u32 size);
extern void GX_LoadBG1Char_020079b0(void *data, u32 offset, u32 size);
extern void GX_LoadBG1Scr_02007630(void *data, u32 offset, u32 size);
extern void GXS_LoadBGPltt_020072b4(void *data, u32 offset, u32 size);
extern void GXS_LoadBG1Char_02007a20(void *data, u32 offset, u32 size);
extern void GXS_LoadBG1Scr_020076a0(void *data, u32 offset, u32 size);
extern void GXS_LoadBG0Scr_020075c0(void *data, u32 offset, u32 size);
extern void GXS_LoadBG2Scr_02007780(void *data, u32 offset, u32 size);
extern BgEntry *func_ov027_020b8558(void *container, int entryId);
extern BgRecord *FindActiveRecordById_020b8184(void *container, u32 recordId);
extern void InitializeResourceContainer_020b8bd4(void *container, ObjManagerConfig *config);
extern void InitObjManagerAndMark_020b9060(void *container, ObjManagerConfig *config);
extern void func_ov027_020b9078(void *container, u32 value);
extern void func_ov027_020b8f98(void *container, u32 resourceId, int count);
extern void SetAllElementObjectModes_020b97fc(void *container, int mode);
extern void NNSi_FndFreeFromDefaultHeap_0202a1c4(void *block);
extern void ZeroHalfThenFree_0202cd78(int handle);
extern ObjElement *func_ov027_020b90a4(void *container, int elementId);
extern void func_ov027_020b9580(void *container, ObjElement *element, BOOL visible);
extern void func_ov027_020b95e4(void *container, ObjElement *element);
extern void func_ov027_020b96a0(void *container, ObjElement *element, int frame);
extern void func_ov027_020b97b8(void *container, ObjElement *element, int mode);
extern fx32 *func_ov027_020b9360(void *container, ObjElement *element, fx32 *position, int mode);
extern void func_ov027_020b91c8(void *container, ObjElement *element, fx32 *position, int mode);
extern void func_ov027_020b9874(void *container, int value);
extern void func_ov027_020b984c(void *container, int value);
extern void ResolveEntryStoreWord_020b9088(void *container, int elementId, void (*callback)(void));
extern s32 CountSetFlagsInRange_02066f7c(void);
extern int func_ov002_02066c78(int a, int b, int c, int d);
extern void LoadAvatarObjPalette_02067b24(BOOL useSubScreen);
extern AvatarInfo *func_ov002_02066fc8(void);
extern void func_ov002_02067a84(VecFx32 *position);
extern void func_ov002_02067c10(void *container, VecFx32 *position);
extern void func_ov002_02068248(void *container, VecFx32 *position, int value);
extern void func_0204f178(void *container, s32 animIndex, int value);
extern BOOL TestContextFlagBit_0206f460(int index);
extern void func_ov015_0206e658(int slotIndex);
extern void func_ov015_02072860(void);
extern void func_ov015_02072878(void);
extern void func_ov015_02072890(void);
extern void func_ov015_020728a8(void);
extern void func_ov015_020728f8(void);
extern void func_ov015_02072814(void);
extern void func_ov002_020626d4(int a, int b);
extern u32 func_0202a9d0(u32 range);

static inline void MI_CpuClearFast(void *dest, u32 size) {
    func_01ff8684(0, dest, size);
}

static inline void SetElementEnabled(void *container, int elementId, BOOL enabled) {
    func_ov027_020b9580(container, func_ov027_020b90a4(container, elementId), enabled);
}

static inline void SetElementMode(void *container, int elementId, int mode) {
    func_ov027_020b97b8(container, func_ov027_020b90a4(container, elementId), mode);
}

static inline void ClearElementNumber(void *container, int elementId) {
    func_ov027_020b95e4(container, func_ov027_020b90a4(container, elementId));
}

static inline void SetElementNumber(void *container, int elementId, u16 value) {
    func_ov027_020b96a0(container, func_ov027_020b90a4(container, elementId), value);
}

void InitPanelScreenGraphics_0206d59c(void)
{
    BgContainerConfig bgMainConfig = data_ov015_02079fc8;
    ObjManagerConfig objMainConfig = data_ov015_0207a034;
    BgContainerConfig bgSubConfig = data_ov015_02079fdc;
    ObjManagerConfig objSubConfig = data_ov015_0207a04c;
    BgGraphicsData bgData;
    fx32 position[2];
    PanelContext *ctx;
    void *container;
    int handle;
    void *archive;
    u32 resourceBase;
    BgEntry *entry;
    BgRecord *record;
    s32 count;
    int tens;
    int value;

    data_ov015_0207e960->flagsE1.active = 0;
    data_ov015_0207e960->flagsE2.ready = 0;
    data_ov015_0207e960->flagsE1.scrolling = 0;
    data_ov015_0207e960->flagsE1.visible = 0;
    data_ov015_0207e960->flagsE1.mode = 0;
    func_ov015_0206c660();
    data_ov015_0207e960->flagsE0.subObjReady = 1;
    data_ov015_0207e960->flagsE0.mainObjReady = 1;
    GX_SetBankForSubOBJExtPltt_02008c24(0x100);
    GX_SetBankForOBJExtPltt_02008784(0x20);
    *(vu32 *)0x04000000 = (*(vu32 *)0x04000000 & ~0x1f00) | 0x1e00;
    *(vu32 *)0x04001000 = (*(vu32 *)0x04001000 & ~0x1f00) | 0x1f00;
    func_ov002_020629a8();
    func_ov002_02062768(1);
    *(vu16 *)0x0400100c = (u16)((*(vu16 *)0x0400100c & 0x43) | 0x284);
    *(vu16 *)0x04001008 = (u16)((*(vu16 *)0x04001008 & ~3) | 2);
    *(vu16 *)0x0400100a = (u16)((*(vu16 *)0x0400100a & ~3) | 3);
    *(vu16 *)0x0400100c = (u16)((*(vu16 *)0x0400100c & ~3) | 1);
    *(vu16 *)0x0400100e = (u16)(*(vu16 *)0x0400100e & ~3);
    MI_CpuClearFast(G2S_GetBG0ScrPtr_02006e14(), 0x800);
    MI_CpuClearFast(G2S_GetBG1ScrPtr_02006e68(), 0x800);
    MI_CpuClearFast(G2S_GetBG2ScrPtr_02006f0c(), 0x800);

    handle = func_0202cc6c(data_ov015_0207e7ec, 0x10, 0);
    func_ov027_020b7d58(data_ov015_0207e960->bgMain, &bgMainConfig);
    resourceBase = (handle + 0x8000U & 0xfffffc) << 7;
    func_ov027_020b7e24(data_ov015_0207e960->bgMain, resourceBase | 0x80000000);
    archive = func_0202c48c(resourceBase | 0x80000002, 0x10);
    GetBgDataFromArchive_0202b554(&bgData, archive, -1, 0, 0);
    func_02007250(bgData.palette->data, 0, bgData.palette->size);
    GX_LoadBG1Char_020079b0(bgData.character->data, 0, bgData.character->size);
    entry = func_ov027_020b8558(data_ov015_0207e960->bgMain, 0);
    GX_LoadBG1Scr_02007630(entry->screen->data, 0, entry->screen->size);
    objMainConfig.cellResourceId = resourceBase | 0x80000004;
    objMainConfig.animResourceId = resourceBase | 0x80000007;
    InitializeResourceContainer_020b8bd4(data_ov015_0207e960->objMain, NULL);
    InitObjManagerAndMark_020b9060(data_ov015_0207e960->objMain, &objMainConfig);
    func_ov027_020b9078(data_ov015_0207e960->objMain, data_ov015_0207e720[3]);
    func_ov027_020b8f98(data_ov015_0207e960->objMain, objMainConfig.animResourceId, 0x19);
    SetAllElementObjectModes_020b97fc(data_ov015_0207e960->objMain, 1);
    NNSi_FndFreeFromDefaultHeap_0202a1c4(archive);
    ZeroHalfThenFree_0202cd78(handle);

    SetElementEnabled(data_ov015_0207e960->objMain, 2, 0);
    SetElementEnabled(data_ov015_0207e960->objMain, 3, 0);
    SetElementEnabled(data_ov015_0207e960->objMain, 0xb, 0);
    count = CountSetFlagsInRange_02066f7c();
    ClearElementNumber(data_ov015_0207e960->objMain, 0x14);
    ClearElementNumber(data_ov015_0207e960->objMain, 0x15);
    SetElementNumber(data_ov015_0207e960->objMain, 0x14, count % 10);
    tens = count / 10 % 10;
    if (tens) {
        SetElementNumber(data_ov015_0207e960->objMain, 0x15, tens);
    } else {
        SetElementEnabled(data_ov015_0207e960->objMain, 0x15, 0);
    }
    ClearElementNumber(data_ov015_0207e960->objMain, 10);
    ctx = data_ov015_0207e960;
    container = ctx->objMain;
    func_ov027_020b96a0(container, func_ov027_020b90a4(container, 10), ctx->level);
    if (func_ov002_02066c78(5, 0, 0, 0) != 0) {
        SetElementEnabled(data_ov015_0207e960->objMain, 8, 1);
        SetElementMode(data_ov015_0207e960->objMain, 8, 0);
    }
    value = func_ov002_02066c78(8, 0, 0, 0);
    if (func_ov002_02066c78(5, 0, 0, 0) != 0) {
        value = 0;
    }
    if (value >= 80) {
        fx32 highPosition[2];

        SetElementEnabled(data_ov015_0207e960->objMain, 0xe, 1);
        container = data_ov015_0207e960->objMain;
        func_ov027_020b9360(container, func_ov027_020b90a4(container, 0xe), highPosition, 0);
        highPosition[0] = ((highPosition[0] >> 12) - 10) << 12;
        container = data_ov015_0207e960->objMain;
        func_ov027_020b91c8(container, func_ov027_020b90a4(container, 0xe), highPosition, 0);
    } else if (value >= 50) {
        fx32 midPosition[2];

        SetElementEnabled(data_ov015_0207e960->objMain, 0xd, 1);
        container = data_ov015_0207e960->objMain;
        func_ov027_020b9360(container, func_ov027_020b90a4(container, 0xd), midPosition, 0);
        midPosition[0] = ((midPosition[0] >> 12) - 10) << 12;
        container = data_ov015_0207e960->objMain;
        func_ov027_020b91c8(container, func_ov027_020b90a4(container, 0xd), midPosition, 0);
    }
    LoadAvatarObjPalette_02067b24(FALSE);
    ctx = data_ov015_0207e960;
    ctx->avatarInfoCopy = *func_ov002_02066fc8();
    ctx->avatarInfo = &ctx->avatarInfoCopy;
    func_ov002_02067a84(&data_ov015_0207e960->avatarPos);
    data_ov015_0207e960->avatarAlpha = 200;
    data_ov015_0207e960->avatarFlags.layer = 1;
    data_ov015_0207e960->avatarPos.x = 0xc6000;
    data_ov015_0207e960->avatarPos.y = 0x29000;
    ctx = data_ov015_0207e960;
    func_ov002_02067c10(ctx->objMain, &ctx->avatarPos);
    ctx = data_ov015_0207e960;
    func_ov002_02068248(ctx->objMain, &ctx->avatarPos, 1);

    handle = func_0202cc6c(data_ov015_0207e7f8, 0x10, 0);
    func_ov027_020b7d58(data_ov015_0207e960->bgSub, &bgSubConfig);
    resourceBase = (handle + 0x8000U & 0xfffffc) << 7;
    func_ov027_020b7e24(data_ov015_0207e960->bgSub, resourceBase | 0x80000003);
    archive = func_0202c48c(resourceBase | 0x80000005, 0x10);
    GetBgDataFromArchive_0202b554(&bgData, archive, -1, 0, 0);
    GXS_LoadBGPltt_020072b4(bgData.palette->data, 0, bgData.palette->size);
    GXS_LoadBG1Char_02007a20(bgData.character->data, 0, bgData.character->size);
    entry = func_ov027_020b8558(data_ov015_0207e960->bgSub, 0);
    GXS_LoadBG1Scr_020076a0(entry->screen->data, 0, entry->screen->size);
    entry = func_ov027_020b8558(data_ov015_0207e960->bgSub, 2);
    FindActiveRecordById_020b8184(data_ov015_0207e960->bgSub, 2);
    GXS_LoadBG0Scr_020075c0(entry->screen->data, 0, entry->screen->size);
    entry = func_ov027_020b8558(data_ov015_0207e960->bgSub, 1);
    record = FindActiveRecordById_020b8184(data_ov015_0207e960->bgSub, 1);
    GXS_LoadBG2Scr_02007780(entry->screen->data, record->offset << 6, entry->screen->size);
    objSubConfig.cellResourceId = resourceBase | 0x80000001;
    objSubConfig.animResourceId = resourceBase | 0x80000007;
    InitializeResourceContainer_020b8bd4(data_ov015_0207e960->objSub, NULL);
    InitObjManagerAndMark_020b9060(data_ov015_0207e960->objSub, &objSubConfig);
    func_ov027_020b9078(data_ov015_0207e960->objSub, data_ov015_0207e720[0]);
    func_ov027_020b8f98(data_ov015_0207e960->objSub, objSubConfig.animResourceId, 0xd);
    SetAllElementObjectModes_020b97fc(data_ov015_0207e960->objSub, 2);
    SetElementMode(data_ov015_0207e960->objSub, 4, 1);
    SetElementMode(data_ov015_0207e960->objSub, 7, 1);
    SetElementMode(data_ov015_0207e960->objSub, 8, 1);
    SetElementMode(data_ov015_0207e960->objSub, 0, 1);
    SetElementMode(data_ov015_0207e960->objSub, 1, 1);
    SetElementMode(data_ov015_0207e960->objSub, 2, 1);
    SetElementMode(data_ov015_0207e960->objSub, 3, 1);
    SetElementMode(data_ov015_0207e960->objSub, 10, 1);
    SetElementMode(data_ov015_0207e960->objSub, 11, 1);
    SetElementMode(data_ov015_0207e960->objSub, 12, 1);
    SetElementMode(data_ov015_0207e960->objSub, 5, 1);
    SetElementMode(data_ov015_0207e960->objSub, 6, 1);
    container = data_ov015_0207e960->objSub;
    func_0204f178(container, func_ov027_020b90a4(container, 1)->animIndex, 0xfb);
    container = data_ov015_0207e960->objSub;
    func_0204f178(container, func_ov027_020b90a4(container, 2)->animIndex, 0xfc);
    container = data_ov015_0207e960->objSub;
    func_0204f178(container, func_ov027_020b90a4(container, 3)->animIndex, 0xfd);
    container = data_ov015_0207e960->objSub;
    func_0204f178(container, func_ov027_020b90a4(container, 5)->animIndex, 0xfe);
    container = data_ov015_0207e960->objSub;
    func_0204f178(container, func_ov027_020b90a4(container, 6)->animIndex, 0xff);
    container = data_ov015_0207e960->objSub;
    func_0204f178(container, func_ov027_020b90a4(container, 10)->animIndex, 6);
    container = data_ov015_0207e960->objSub;
    func_0204f178(container, func_ov027_020b90a4(container, 11)->animIndex, 5);
    container = data_ov015_0207e960->objSub;
    func_0204f178(container, func_ov027_020b90a4(container, 12)->animIndex, 4);
    container = data_ov015_0207e960->objSub;
    func_0204f178(container, func_ov027_020b90a4(container, 4)->animIndex, 3);
    container = data_ov015_0207e960->objSub;
    func_0204f178(container, func_ov027_020b90a4(container, 7)->animIndex, 2);
    container = data_ov015_0207e960->objSub;
    func_0204f178(container, func_ov027_020b90a4(container, 8)->animIndex, 1);
    container = data_ov015_0207e960->objSub;
    func_0204f178(container, func_ov027_020b90a4(container, 0)->animIndex, 0);
    SetElementEnabled(data_ov015_0207e960->objSub, 10, 0);
    SetElementEnabled(data_ov015_0207e960->objSub, 11, 0);
    SetElementEnabled(data_ov015_0207e960->objSub, 12, 0);
    LoadAvatarObjPalette_02067b24(TRUE);
    container = data_ov015_0207e960->objSub;
    data_ov015_0207e960->slotY[0] = func_ov027_020b9360(container, func_ov027_020b90a4(container, 1), position, 0)[1];
    container = data_ov015_0207e960->objSub;
    data_ov015_0207e960->slotY[1] = func_ov027_020b9360(container, func_ov027_020b90a4(container, 2), position, 0)[1];
    container = data_ov015_0207e960->objSub;
    data_ov015_0207e960->slotY[2] = func_ov027_020b9360(container, func_ov027_020b90a4(container, 3), position, 0)[1];
    if (TestContextFlagBit_0206f460(0) && (data_ov015_0207e960->flagsE1.slotCleared & 1) == 0) {
        func_ov015_0206e658(0);
        SetElementEnabled(data_ov015_0207e960->objSub, 10, 1);
    }
    if (TestContextFlagBit_0206f460(1) && (data_ov015_0207e960->flagsE1.slotCleared & 2) == 0) {
        func_ov015_0206e658(1);
        SetElementEnabled(data_ov015_0207e960->objSub, 11, 1);
    }
    if (TestContextFlagBit_0206f460(2) && (data_ov015_0207e960->flagsE1.slotCleared & 4) == 0) {
        func_ov015_0206e658(2);
        SetElementEnabled(data_ov015_0207e960->objSub, 12, 1);
    }
    func_ov027_020b9874(data_ov015_0207e960->objSub, 1);
    func_ov027_020b984c(data_ov015_0207e960->objSub, 1);
    ResolveEntryStoreWord_020b9088(data_ov015_0207e960->objSub, 1, func_ov015_02072860);
    ResolveEntryStoreWord_020b9088(data_ov015_0207e960->objSub, 2, func_ov015_02072878);
    ResolveEntryStoreWord_020b9088(data_ov015_0207e960->objSub, 3, func_ov015_02072890);
    ResolveEntryStoreWord_020b9088(data_ov015_0207e960->objSub, 7, func_ov015_020728a8);
    ResolveEntryStoreWord_020b9088(data_ov015_0207e960->objSub, 8, func_ov015_020728f8);
    ResolveEntryStoreWord_020b9088(data_ov015_0207e960->objSub, 9, func_ov015_02072814);
    NNSi_FndFreeFromDefaultHeap_0202a1c4(archive);
    ZeroHalfThenFree_0202cd78(handle);
    func_ov002_020626d4(0, 1);
    *(vu32 *)0x0400001c = 0x1ec0000;
    data_ov015_0207e960->scrollMainX = func_0202a9d0(0x1000) + 0x1000;
    data_ov015_0207e960->scrollMainY = (func_0202a9d0(0x70) + 0x10) << 12;
    data_ov015_0207e960->scrollSubX = func_0202a9d0(0x1000) + 0x1000;
    data_ov015_0207e960->scrollSubY = (func_0202a9d0(0x70) + 0x80) << 12;
    data_ov015_0207e960->flagsE1.active = 1;
    data_ov015_0207e960->flagsE2.ready = 1;
    data_ov015_0207e960->flagsE2.busy = 0;
    data_ov015_0207e960->flagsE1.scrolling = 1;
    data_ov015_0207e960->flagsE1.visible = 1;
    if (func_ov002_02066c78(5, 0, 0, 0) != 0) {
        data_ov015_0207e960->flagsE1.mode = 2;
    }
}
