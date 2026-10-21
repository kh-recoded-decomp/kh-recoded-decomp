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
    u8 pad_00[0xc];
    s32 value;
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
    u8 cardShown : 1;
    u8 pad7 : 1;
} MenuFlags98;

typedef struct MenuFlags99 {
    u8 visible : 1;
    u8 pad1_7 : 7;
} MenuFlags99;

typedef struct MenuState {
    u8 pad_00[0x14];
    s32 focusValue;
    u8 records[0x98 - 0x18];
    MenuFlags98 flags98;
    MenuFlags99 flags99;
    u8 pad_9a[0x304 - 0x9a];
    u8 bgMain[0x98];
    u8 objMain[0xcc94 - 0x39c];
    AvatarView view;
    CardHeader savedCard;
} MenuState;

typedef struct SessionInfo {
    s32 score;
    u16 checksum;
    u16 exitMode : 3;
    u16 showCard : 1;
    u16 resumed : 1;
    u16 rank : 3;
    u16 avatar : 5;
    u16 hasBonus : 1;
    u8 stage;
    u8 world;
    u8 progress;
    u8 pad_0B[0x10 - 0xb];
    s8 base;
    s8 offset;
    s8 slot;
    u8 linked;
    s8 cardLoaded;
    u8 pad_15[3];
    s32 recordId;
} SessionInfo;

extern MenuState *data_ov013_02074ce0;
extern BgContainerConfig data_ov013_020749f4;
extern ObjManagerConfig data_ov013_02074a74;
extern char data_ov013_02074c64[];
extern u32 data_ov013_02074b20[];
extern SessionInfo data_0206085c;

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
extern void func_ov027_020b96a0(void *container, ObjElement *element, int frame);
extern void SetFocusedWidget_020b96e4(void *container, ObjElement *element);
extern void RecordPanelClear_02070f50(int index);
extern int DispatchContextCommand_02066c78(u32 command, int value, int extra, void *buffer);
extern void func_01ff8830(void *dst, int value, u32 size);
extern s32 PickRandomUnflaggedRecord_0206a214(void *card, int flags);
extern void CopyRecordTableBField_02069d04(s32 index, void *dst);
extern void LoadAvatarObjPalette_02067b24(BOOL useSubScreen);
extern void SelectCategoryRecord_02067fd8(void *container, AvatarView *view, s32 recordId);
extern void func_ov002_02068248(void *container, AvatarView *view, int value);
extern void func_ov027_020b9098(void *container, void *callback);
extern void ResolveEntryStoreWord_020b9088(void *container, int slot, void *callback);
extern void func_ov013_0207445c(void);
extern void SetPanelModeWithSound_020746d0(void);
extern void func_ov013_020746f4(void);

static inline int OpenResultArchive(void)
{
    return func_0202cc6c(data_ov013_02074c64, 0x10, 0);
}

static inline u32 GetResourceBase(int handle)
{
    return (handle + 0x8000U & 0xfffffc) << 7;
}

void InitRecordResultScreen_0206df40(int entry)
{
    BgContainerConfig bgConfig = data_ov013_020749f4;
    ObjManagerConfig objConfig = data_ov013_02074a74;
    BgGraphicsData bgData;
    int handle;
    void *archive;
    BgEntry *screen;
    void *container;
    int i;
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
    handle = OpenResultArchive();
    func_ov002_020629b8();
    *(vu16 *)0x04000008 = (u16)((*(vu16 *)0x04000008 & ~3) | 2);
    *(vu16 *)0x0400000a = (u16)((*(vu16 *)0x0400000a & ~3) | 3);
    *(vu16 *)0x0400000c = (u16)((*(vu16 *)0x0400000c & ~3) | 1);
    *(vu16 *)0x0400000e = (u16)(*(vu16 *)0x0400000e & ~3);
    GX_SetBankForOBJExtPltt_02008784(0x20);
    *(vu32 *)0x04000000 = (*(vu32 *)0x04000000 & ~0x1f00) | 0x1f00;
    func_ov027_020b7d58(data_ov013_02074ce0->bgMain, &bgConfig);
    func_ov027_020b7e24(data_ov013_02074ce0->bgMain, GetResourceBase(handle) | 0x80000000);
    archive = func_0202c48c(GetResourceBase(handle) | 0x80000001, 0x10);
    GetBgDataFromArchive_0202b554(&bgData, archive, -1, 0, 0);
    func_02007250(bgData.palette->data, 0, bgData.palette->size);
    GX_LoadBG1Char_020079b0(bgData.character->data, 0, bgData.character->size);
    screen = func_ov027_020b8558(data_ov013_02074ce0->bgMain, 0);
    GX_LoadBG1Scr_02007630(screen->screen->data, 0, screen->screen->size);
    if (data_0206085c.showCard) {
        screen = func_ov027_020b8558(data_ov013_02074ce0->bgMain, 1);
        GX_LoadBG0Scr_02007550(screen->screen->data, 0, screen->screen->size);
        objConfig.cellResourceId = GetResourceBase(handle) | 0x80000002;
        objConfig.animResourceId = GetResourceBase(handle) | 0x80000003;
    } else {
        screen = func_ov027_020b8558(data_ov013_02074ce0->bgMain, 2);
        GX_LoadBG0Scr_02007550(screen->screen->data, 0, screen->screen->size);
        objConfig.cellResourceId = GetResourceBase(handle) | 0x80000002;
        objConfig.animResourceId = GetResourceBase(handle) | 0x80000003;
    }
    InitializeResourceContainer_020b8bd4(data_ov013_02074ce0->objMain, NULL);
    InitObjManagerAndMark_020b9060(data_ov013_02074ce0->objMain, &objConfig);
    func_ov027_020b9078(data_ov013_02074ce0->objMain, data_ov013_02074b20[3]);
    func_ov027_020b8f98(data_ov013_02074ce0->objMain, objConfig.animResourceId, 0xe);
    data_ov013_02074ce0->flags98.objReady = 1;
    SetAllElementObjectModes_020b97fc(data_ov013_02074ce0->objMain, 3);
    NNSi_FndFreeFromDefaultHeap_0202a1c4(archive);
    ZeroHalfThenFree_0202cd78(handle);

    if (data_0206085c.world == data_0206085c.stage) {
        container = data_ov013_02074ce0->objMain;
        SetFocusedWidget_020b96e4(container, func_ov027_020b90a4(container, 4));
        container = data_ov013_02074ce0->objMain;
        func_ov027_020b9580(container, func_ov027_020b90a4(container, 3), 0);
        data_ov013_02074ce0->focusValue = func_ov027_020b90a4(data_ov013_02074ce0->objMain, 4)->value;
    } else {
        container = data_ov013_02074ce0->objMain;
        SetFocusedWidget_020b96e4(container, func_ov027_020b90a4(container, 3));
        data_ov013_02074ce0->focusValue = func_ov027_020b90a4(data_ov013_02074ce0->objMain, 3)->value;
    }
    if (!data_0206085c.showCard) {
        container = data_ov013_02074ce0->objMain;
        func_ov027_020b9580(container, func_ov027_020b90a4(container, 5), 1);
        container = data_ov013_02074ce0->objMain;
        func_ov027_020b9580(container, func_ov027_020b90a4(container, 6), 1);
        container = data_ov013_02074ce0->objMain;
        func_ov027_020b9580(container, func_ov027_020b90a4(container, 7), 0);
    }
    for (i = 0; i < 7; i++) {
        container = data_ov013_02074ce0->objMain;
        func_ov027_020b95e4(container, func_ov027_020b90a4(container, i + 10));
        container = data_ov013_02074ce0->objMain;
        func_ov027_020b9580(container, func_ov027_020b90a4(container, i + 10), 0);
    }
    value = data_0206085c.score;
    digit = 0;
    do {
        container = data_ov013_02074ce0->objMain;
        func_ov027_020b9580(container, func_ov027_020b90a4(container, digit + 10), 1);
        container = data_ov013_02074ce0->objMain;
        func_ov027_020b96a0(container, func_ov027_020b90a4(container, digit + 10), (u16)(value % 10));
        digit++;
        value /= 10;
    } while (value != 0);

    RecordPanelClear_02070f50(data_0206085c.offset + data_0206085c.base);
    if (data_0206085c.showCard) {
        if (data_0206085c.cardLoaded == 0) {
            PlayerCard card;

            func_01ff8830(&card, 0, sizeof(PlayerCard));
            DispatchContextCommand_02066c78(0, entry - (entry + 1) / 10, 0, &card);
            data_0206085c.cardLoaded = 1;
            data_0206085c.recordId = PickRandomUnflaggedRecord_0206a214(&card, 0);
            data_ov013_02074ce0->flags98.cardShown = 1;
        }
        CopyRecordTableBField_02069d04(data_0206085c.recordId, data_ov013_02074ce0->records);
        func_01ff8830(&data_ov013_02074ce0->savedCard, 0, sizeof(CardHeader));
        LoadAvatarObjPalette_02067b24(FALSE);
        data_ov013_02074ce0->view.card = &data_ov013_02074ce0->savedCard;
        data_ov013_02074ce0->view.alpha = 200;
        data_ov013_02074ce0->view.flags.layer = 0;
        data_ov013_02074ce0->view.pos.x = 0x80000;
        data_ov013_02074ce0->view.pos.y = 0x40000;
        SelectCategoryRecord_02067fd8(data_ov013_02074ce0->objMain, &data_ov013_02074ce0->view, data_0206085c.recordId);
        func_ov002_02068248(data_ov013_02074ce0->objMain, &data_ov013_02074ce0->view, 1);
    }
    func_ov027_020b9098(data_ov013_02074ce0->objMain, func_ov013_0207445c);
    ResolveEntryStoreWord_020b9088(data_ov013_02074ce0->objMain, 3, SetPanelModeWithSound_020746d0);
    ResolveEntryStoreWord_020b9088(data_ov013_02074ce0->objMain, 4, func_ov013_020746f4);
}
