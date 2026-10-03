#include "nitro/types.h"

typedef struct BgContainerConfig {
    u32 values[5];
} BgContainerConfig;

typedef struct ObjManagerConfig {
    u32 cellResourceId;
    u32 pad_04[4];
    u32 animResourceId;
} ObjManagerConfig;

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

typedef struct ObjElement {
    u8 pad_00[0x14];
    s32 animIndex;
} ObjElement;

typedef struct MenuFlags98 {
    u8 pad0_2 : 3;
    u8 loaded : 1;
    u8 objReady : 1;
    u8 active : 1;
    u8 pad6_7 : 2;
} MenuFlags98;

typedef struct MenuFlags99 {
    u8 visible : 1;
    u8 pad1 : 1;
    u8 ready : 1;
    u8 pad3_5 : 3;
    u8 busy : 1;
    u8 pad7 : 1;
} MenuFlags99;

typedef struct MenuFlagsD259 {
    u8 skipA : 1;
    u8 skipB : 1;
    u8 pad2_7 : 6;
} MenuFlagsD259;

typedef struct MenuState {
    u8 pad_00[0xa];
    u16 paletteWord;
    u16 paletteWordCopy;
    u8 pad_0e[0x98 - 0xe];
    MenuFlags98 flags98;
    MenuFlags99 flags99;
    u8 pad_9a[0x304 - 0x9a];
    u8 bgMain[0x98];
    u8 objMain[0x647c];
    u8 objSub[0x647c];
    u8 pad_cc94[0xd259 - 0xcc94];
    MenuFlagsD259 flagsD259;
} MenuState;

extern MenuState *data_ov013_02074ce0;
extern BgContainerConfig data_ov013_02074a08;
extern ObjManagerConfig data_ov013_02074a5c;
extern char data_ov013_02074c4c[];
extern u32 data_ov013_02074b20[];

extern void func_ov027_020b7dfc(void *container);
extern void DestroyObjectsAndRelease_020b8c58(void *container);
extern int func_0202cc6c(const char *path, u32 kind, u32 fromTop);
extern void func_ov002_020629b8(void);
extern void GX_SetBankForOBJExtPltt_02008784(int bank);
extern void func_ov027_020b7d58(void *container, BgContainerConfig *config);
extern void func_ov027_020b7e24(void *container, u32 resourceId);
extern void *func_0202c48c(u32 resourceId, u32 kind);
extern void GetBgDataFromArchive_0202b554(BgGraphicsData *out, void *archive, int screenIndex, int characterIndex,
                                          int paletteIndex);
extern void func_02007250(void *data, u32 offset, u32 size);
extern void GX_LoadBG1Char_020079b0(void *data, u32 offset, u32 size);
extern void GX_LoadBG1Scr_02007630(void *data, u32 offset, u32 size);
extern void GX_LoadBG0Scr_02007550(void *data, u32 offset, u32 size);
extern BgEntry *func_ov027_020b8558(void *container, int entryId);
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
extern void func_ov027_020b97b8(void *container, ObjElement *element, int mode);
extern void LoadAvatarObjPalette_02067b24(BOOL useSubScreen);
extern void SetPanelPhase_0207174c(int phase);
extern void func_02007d90(void);
extern void GX_EndLoadOBJExtPltt_02007e48(void);
extern void func_ov002_020626d4(int a, int b);

void InitMenuScreenGraphics_0206cb80(void)
{
    BgContainerConfig bgConfig = data_ov013_02074a08;
    ObjManagerConfig objConfig = data_ov013_02074a5c;
    BgGraphicsData bgData;
    void *container;
    int handle;
    void *archive;
    u32 resourceBase;
    BgEntry *entry;

    if (data_ov013_02074ce0->flags98.loaded) {
        data_ov013_02074ce0->flags98.active = 0;
        data_ov013_02074ce0->flags99.visible = 0;
        func_ov027_020b7dfc(data_ov013_02074ce0->bgMain);
        DestroyObjectsAndRelease_020b8c58(data_ov013_02074ce0->objMain);
        data_ov013_02074ce0->flags98.objReady = 0;
        data_ov013_02074ce0->flags99.ready = 0;
        data_ov013_02074ce0->flags99.busy = 0;
    }
    data_ov013_02074ce0->flags98.loaded = 1;
    handle = func_0202cc6c(data_ov013_02074c4c, 0x10, 0);
    func_ov002_020629b8();
    GX_SetBankForOBJExtPltt_02008784(0x20);
    *(vu32 *)0x04000000 = (*(vu32 *)0x04000000 & ~0x1f00) | 0x1e00;
    func_ov027_020b7d58(data_ov013_02074ce0->bgMain, &bgConfig);
    resourceBase = (handle + 0x8000U & 0xfffffc) << 7;
    func_ov027_020b7e24(data_ov013_02074ce0->bgMain, resourceBase | 0x80000000);
    archive = func_0202c48c(resourceBase | 0x80000002, 0x10);
    GetBgDataFromArchive_0202b554(&bgData, archive, -1, 0, 0);
    func_02007250(bgData.palette->data, 0, bgData.palette->size);
    GX_LoadBG1Char_020079b0(bgData.character->data, 0, bgData.character->size);
    entry = func_ov027_020b8558(data_ov013_02074ce0->bgMain, 0);
    GX_LoadBG1Scr_02007630(entry->screen->data, 0, entry->screen->size);
    entry = func_ov027_020b8558(data_ov013_02074ce0->bgMain, 1);
    GX_LoadBG0Scr_02007550(entry->screen->data, 0, entry->screen->size);
    *(vu16 *)0x04000008 = (u16)((*(vu16 *)0x04000008 & ~3) | 2);
    *(vu16 *)0x0400000a = (u16)((*(vu16 *)0x0400000a & ~3) | 3);
    *(vu16 *)0x0400000c = (u16)((*(vu16 *)0x0400000c & ~3) | 1);
    *(vu16 *)0x0400000e = (u16)(*(vu16 *)0x0400000e & ~3);
    objConfig.cellResourceId = resourceBase | 0x80000004;
    objConfig.animResourceId = resourceBase | 0x80000007;
    InitializeResourceContainer_020b8bd4(data_ov013_02074ce0->objMain, NULL);
    InitObjManagerAndMark_020b9060(data_ov013_02074ce0->objMain, &objConfig);
    func_ov027_020b9078(data_ov013_02074ce0->objMain, data_ov013_02074b20[2]);
    func_ov027_020b8f98(data_ov013_02074ce0->objMain, objConfig.animResourceId, 0x19);
    data_ov013_02074ce0->flags98.objReady = 1;
    SetAllElementObjectModes_020b97fc(data_ov013_02074ce0->objMain, 3);
    NNSi_FndFreeFromDefaultHeap_0202a1c4(archive);
    ZeroHalfThenFree_0202cd78(handle);

    container = data_ov013_02074ce0->objMain;
    func_ov027_020b9580(container, func_ov027_020b90a4(container, 0xb), 0);
    container = data_ov013_02074ce0->objMain;
    func_ov027_020b9580(container, func_ov027_020b90a4(container, 2), 0);
    container = data_ov013_02074ce0->objMain;
    func_ov027_020b9580(container, func_ov027_020b90a4(container, 3), 0);
    container = data_ov013_02074ce0->objMain;
    func_ov027_020b9580(container, func_ov027_020b90a4(container, 0xf), 1);
    container = data_ov013_02074ce0->objMain;
    func_ov027_020b95e4(container, func_ov027_020b90a4(container, 0x14));
    container = data_ov013_02074ce0->objMain;
    func_ov027_020b95e4(container, func_ov027_020b90a4(container, 0x15));
    container = data_ov013_02074ce0->objMain;
    func_ov027_020b95e4(container, func_ov027_020b90a4(container, 10));
    container = data_ov013_02074ce0->objMain;
    func_ov027_020b97b8(container, func_ov027_020b90a4(container, 8), 0);
    LoadAvatarObjPalette_02067b24(FALSE);
    if (!data_ov013_02074ce0->flagsD259.skipA && !data_ov013_02074ce0->flagsD259.skipB) {
        SetPanelPhase_0207174c(1);
    }
    func_02007d90();
    data_ov013_02074ce0->paletteWord = *(u16 *)0x06890002;
    data_ov013_02074ce0->paletteWordCopy = data_ov013_02074ce0->paletteWord;
    GX_EndLoadOBJExtPltt_02007e48();
    func_ov002_020626d4(0, 1);
    *(vu32 *)0x0400001c = 0x1ec0000;
    data_ov013_02074ce0->flags98.active = 1;
    data_ov013_02074ce0->flags99.visible = 1;
    data_ov013_02074ce0->flags99.ready = 1;
}
