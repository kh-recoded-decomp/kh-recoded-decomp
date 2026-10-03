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

typedef struct PlayerCard {
    u8 pad_00[0x68];
    u8 avatarFrame;
    u8 pad_69[7];
} PlayerCard;

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
    u8 pad_00[0xe0];
    ScreenFlagsE0 flagsE0;
    ScreenFlagsE1 flagsE1;
    ScreenFlagsE2 flagsE2;
    u8 pad_e3[0xec - 0xe3];
    s32 cardIndex;
    u8 pad_f0[0x100 - 0xf0];
    VecFx32 avatarPos;
    u8 pad_10c[0x118 - 0x10c];
    PlayerCard *avatarCard;
    u8 pad_11c[0x5aa - 0x11c];
    u8 avatarAlpha;
    AvatarFlags avatarFlags;
    u8 bgMain[0x98];
    u8 objMain[0xc914];
    PlayerCard cards[1];
} PanelContext;

extern PanelContext *data_ov015_0207e960;
extern BgContainerConfig data_ov015_02079ff0;
extern ObjManagerConfig data_ov015_0207a064;
extern char data_ov015_0207e7f8[];
extern u32 data_ov015_0207e720[];

extern void func_ov015_0206c670(void);
extern void GX_SetBankForOBJExtPltt_02008784(int bank);
extern void GX_SetBankForSubOBJExtPltt_02008c24(int bank);
extern void *G2_GetBG0ScrPtr_02006de0(void);
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
extern void func_ov027_020b96a0(void *container, ObjElement *element, int frame);
extern void LoadAvatarObjPalette_02067b24(BOOL useSubScreen);
extern void func_ov002_02067a84(VecFx32 *position);
extern void func_ov002_02067c10(void *container, VecFx32 *position);
extern void func_ov002_02068248(void *container, VecFx32 *position, int value);

void InitPanelMainScreen_0206e730(void)
{
    BgContainerConfig bgConfig = data_ov015_02079ff0;
    ObjManagerConfig objConfig = data_ov015_0207a064;
    BgGraphicsData bgData;
    PanelContext *ctx;
    void *container;
    int handle;
    void *archive;
    u32 resourceBase;
    BgEntry *entry;

    data_ov015_0207e960->flagsE1.active = 0;
    data_ov015_0207e960->flagsE2.ready = 0;
    data_ov015_0207e960->flagsE1.scrolling = 0;
    data_ov015_0207e960->flagsE1.visible = 0;
    data_ov015_0207e960->flagsE1.mode = 0;
    func_ov015_0206c670();
    data_ov015_0207e960->flagsE0.subObjReady = 1;
    GX_SetBankForOBJExtPltt_02008784(0x20);
    GX_SetBankForSubOBJExtPltt_02008c24(0x100);
    *(vu32 *)0x04000000 = (*(vu32 *)0x04000000 & ~0x1f00) | 0x1e00;
    func_01ff8684(0, G2_GetBG0ScrPtr_02006de0(), 0x800);

    handle = func_0202cc6c(data_ov015_0207e7f8, 0x10, 0);
    func_ov027_020b7d58(data_ov015_0207e960->bgMain, &bgConfig);
    resourceBase = (handle + 0x8000U & 0xfffffc) << 7;
    func_ov027_020b7e24(data_ov015_0207e960->bgMain, resourceBase | 0x80000002);
    archive = func_0202c48c(resourceBase | 0x80000004, 0x10);
    GetBgDataFromArchive_0202b554(&bgData, archive, -1, 0, 0);
    func_02007250(bgData.palette->data, 0, bgData.palette->size);
    GX_LoadBG1Char_020079b0(bgData.character->data, 0, bgData.character->size);
    entry = func_ov027_020b8558(data_ov015_0207e960->bgMain, 0);
    GX_LoadBG1Scr_02007630(entry->screen->data, 0, entry->screen->size);
    objConfig.cellResourceId = resourceBase | 0x80000000;
    objConfig.animResourceId = resourceBase | 0x80000006;
    InitializeResourceContainer_020b8bd4(data_ov015_0207e960->objMain, NULL);
    InitObjManagerAndMark_020b9060(data_ov015_0207e960->objMain, &objConfig);
    func_ov027_020b9078(data_ov015_0207e960->objMain, data_ov015_0207e720[2]);
    func_ov027_020b8f98(data_ov015_0207e960->objMain, objConfig.animResourceId, 5);
    SetAllElementObjectModes_020b97fc(data_ov015_0207e960->objMain, 1);
    NNSi_FndFreeFromDefaultHeap_0202a1c4(archive);
    ZeroHalfThenFree_0202cd78(handle);

    container = data_ov015_0207e960->objMain;
    func_ov027_020b9580(container, func_ov027_020b90a4(container, 0), 1);
    container = data_ov015_0207e960->objMain;
    func_ov027_020b9580(container, func_ov027_020b90a4(container, 1), 1);
    container = data_ov015_0207e960->objMain;
    func_ov027_020b95e4(container, func_ov027_020b90a4(container, 0));
    container = data_ov015_0207e960->objMain;
    func_ov027_020b95e4(container, func_ov027_020b90a4(container, 1));
    container = data_ov015_0207e960->objMain;
    func_ov027_020b96a0(container, func_ov027_020b90a4(container, 1), 6);
    ctx = data_ov015_0207e960;
    container = ctx->objMain;
    func_ov027_020b96a0(container, func_ov027_020b90a4(container, 0), ctx->cards[ctx->cardIndex].avatarFrame);
    LoadAvatarObjPalette_02067b24(TRUE);
    ctx = data_ov015_0207e960;
    ctx->avatarCard = &ctx->cards[ctx->cardIndex];
    func_ov002_02067a84(&data_ov015_0207e960->avatarPos);
    data_ov015_0207e960->avatarAlpha = 200;
    data_ov015_0207e960->avatarFlags.layer = 1;
    data_ov015_0207e960->avatarPos.x = 0xc8000;
    data_ov015_0207e960->avatarPos.y = 0x32000;
    ctx = data_ov015_0207e960;
    func_ov002_02067c10(ctx->objMain, &ctx->avatarPos);
    ctx = data_ov015_0207e960;
    func_ov002_02068248(ctx->objMain, &ctx->avatarPos, 1);
    data_ov015_0207e960->flagsE1.active = 1;
    data_ov015_0207e960->flagsE2.ready = 1;
    data_ov015_0207e960->flagsE2.busy = 0;
}
