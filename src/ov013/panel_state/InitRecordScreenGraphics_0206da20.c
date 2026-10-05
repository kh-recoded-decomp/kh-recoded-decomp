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

typedef struct CardHeader {
    u32 words[4];
} CardHeader;

typedef struct PlayerCard {
    CardHeader header;
    u8 pad_10[0x58];
    u8 avatarFrame;
    u8 pad_69[7];
} PlayerCard;

typedef struct AvatarFlags {
    u8 layer : 2;
    u8 pad2_7 : 6;
} AvatarFlags;

typedef struct AvatarView {
    VecFx32 pos;
    u8 pad_0c[0x18 - 0xc];
    CardHeader *card;
    u8 pad_1c[0x4aa - 0x1c];
    u8 alpha;
    AvatarFlags flags;
} AvatarView;

typedef struct MenuFlags98 {
    u8 pad0_2 : 3;
    u8 loaded : 1;
    u8 objReady : 1;
    u8 active : 1;
    u8 pad6_7 : 2;
} MenuFlags98;

typedef struct MenuFlags99 {
    u8 visible : 1;
    u8 pad1_7 : 7;
} MenuFlags99;

typedef struct MenuState {
    u8 pad_00[0x98];
    MenuFlags98 flags98;
    MenuFlags99 flags99;
    u8 pad_9a[0x304 - 0x9a];
    u8 bgMain[0x98];
    u8 objMain[0xcc94 - 0x39c];
    AvatarView view;
    CardHeader savedCard;
} MenuState;

extern MenuState *data_ov013_02074ce0;
extern BgContainerConfig data_ov013_02074a30;
extern ObjManagerConfig data_ov013_02074a44;
extern char data_ov013_02074c58[];
extern u32 data_ov013_02074b20[];
extern int data_0206085c;

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
extern void func_ov027_020b97b8(void *container, ObjElement *element, int mode);
extern int func_ov013_02070cb4(void);
extern int DispatchContextCommand_02066c78(u32 command, int value, int extra, void *buffer);
extern void func_01ff8830(void *dst, int value, u32 size);
extern void LoadAvatarObjPalette_02067b24(BOOL useSubScreen);
extern void func_ov002_02067a84(AvatarView *view);
extern void func_ov002_02067c10(void *container, AvatarView *view);
extern void func_ov002_02068248(void *container, AvatarView *view, int value);
extern void func_ov002_020626d4(int a, int b);

void InitRecordScreenGraphics_0206da20(void)
{
    BgContainerConfig bgConfig = data_ov013_02074a30;
    ObjManagerConfig objConfig = data_ov013_02074a44;
    PlayerCard card;
    BgGraphicsData bgData;
    int i;
    MenuState *ctx;
    void *container;
    int handle;
    void *archive;
    u32 resourceBase;
    BgEntry *entry;
    int value;
    int digit;

    if (data_ov013_02074ce0->flags98.loaded) {
        data_ov013_02074ce0->flags98.active = 0;
        data_ov013_02074ce0->flags99.visible = 0;
        func_ov027_020b7dfc(data_ov013_02074ce0->bgMain);
        DestroyObjectsAndRelease_020b8c58(data_ov013_02074ce0->objMain);
        data_ov013_02074ce0->flags98.objReady = 0;
    }
    data_ov013_02074ce0->flags98.loaded = 1;
    handle = func_0202cc6c(data_ov013_02074c58, 0x10, 0);
    func_ov002_020629b8();
    GX_SetBankForOBJExtPltt_02008784(0x20);
    *(vu32 *)0x04000000 = (*(vu32 *)0x04000000 & ~0x1f00) | 0x1e00;
    func_ov027_020b7d58(data_ov013_02074ce0->bgMain, &bgConfig);
    resourceBase = (handle + 0x8000U & 0xfffffc) << 7;
    func_ov027_020b7e24(data_ov013_02074ce0->bgMain, resourceBase | 0x80000000);
    archive = func_0202c48c(resourceBase | 0x80000001, 0x10);
    GetBgDataFromArchive_0202b554(&bgData, archive, -1, 0, 0);
    func_02007250(bgData.palette->data, 0, bgData.palette->size);
    GX_LoadBG1Char_020079b0(bgData.character->data, 0, bgData.character->size);
    entry = func_ov027_020b8558(data_ov013_02074ce0->bgMain, 0);
    GX_LoadBG1Scr_02007630(entry->screen->data, 0, entry->screen->size);
    objConfig.cellResourceId = resourceBase | 0x80000002;
    objConfig.animResourceId = resourceBase | 0x80000003;
    InitializeResourceContainer_020b8bd4(data_ov013_02074ce0->objMain, NULL);
    InitObjManagerAndMark_020b9060(data_ov013_02074ce0->objMain, &objConfig);
    func_ov027_020b9078(data_ov013_02074ce0->objMain, data_ov013_02074b20[1]);
    func_ov027_020b8f98(data_ov013_02074ce0->objMain, objConfig.animResourceId, 0xd);
    data_ov013_02074ce0->flags98.objReady = 1;
    SetAllElementObjectModes_020b97fc(data_ov013_02074ce0->objMain, 1);
    NNSi_FndFreeFromDefaultHeap_0202a1c4(archive);
    ZeroHalfThenFree_0202cd78(handle);

    for (i = 0; i < 7; i++) {
        container = data_ov013_02074ce0->objMain;
        func_ov027_020b95e4(container, func_ov027_020b90a4(container, i + 10));
        container = data_ov013_02074ce0->objMain;
        func_ov027_020b9580(container, func_ov027_020b90a4(container, i + 10), 0);
    }
    func_ov027_020b97b8(data_ov013_02074ce0->objMain, func_ov027_020b90a4(data_ov013_02074ce0->objMain, 4), 0);
    DispatchContextCommand_02066c78(0, func_ov013_02070cb4(), 0, &card);
    container = data_ov013_02074ce0->objMain;
    func_ov027_020b9580(container, func_ov027_020b90a4(container, 5), 1);
    container = data_ov013_02074ce0->objMain;
    func_ov027_020b95e4(container, func_ov027_020b90a4(container, 5));
    func_ov027_020b96a0(data_ov013_02074ce0->objMain, func_ov027_020b90a4(data_ov013_02074ce0->objMain, 5),
                        card.avatarFrame);
    container = data_ov013_02074ce0->objMain;
    func_ov027_020b9580(container, func_ov027_020b90a4(container, 6), 1);
    container = data_ov013_02074ce0->objMain;
    func_ov027_020b9580(container, func_ov027_020b90a4(container, 3), 1);

    value = data_0206085c;
    digit = 0;
    do {
        container = data_ov013_02074ce0->objMain;
        func_ov027_020b9580(container, func_ov027_020b90a4(container, digit + 10), 1);
        container = data_ov013_02074ce0->objMain;
        func_ov027_020b96a0(container, func_ov027_020b90a4(container, digit + 10), (u16)(value % 10));
        digit++;
        value /= 10;
    } while (value != 0);

    func_01ff8830(&data_ov013_02074ce0->view, 0, sizeof(AvatarView));
    func_01ff8830(&data_ov013_02074ce0->savedCard, 0, sizeof(CardHeader));
    LoadAvatarObjPalette_02067b24(FALSE);
    DispatchContextCommand_02066c78(0, func_ov013_02070cb4(), 0, &card);
    ctx = data_ov013_02074ce0;
    ctx->savedCard = card.header;
    ctx->view.card = &ctx->savedCard;
    func_ov002_02067a84(&data_ov013_02074ce0->view);
    data_ov013_02074ce0->view.alpha = 200;
    data_ov013_02074ce0->view.flags.layer = 1;
    data_ov013_02074ce0->view.pos.x = 0xc6000;
    data_ov013_02074ce0->view.pos.y = 0x64000;
    ctx = data_ov013_02074ce0;
    func_ov002_02067c10(ctx->objMain, &ctx->view);
    ctx = data_ov013_02074ce0;
    func_ov002_02068248(ctx->objMain, &ctx->view, 1);
    func_ov002_020626d4(0, 1);
    *(vu32 *)0x0400001c = 0x1b50000;
    data_ov013_02074ce0->flags99.visible = 1;
}
