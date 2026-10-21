#pragma opt_dead_assignments off
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

typedef struct ProfileBlock {
    u32 words[4];
} ProfileBlock;

typedef struct TileRange {
    u32 first;
    u32 second;
} TileRange;

typedef struct TileTableDesc {
    TileRange *range;
    u32 width;
    u32 height;
    u32 flags;
} TileTableDesc;

typedef struct TileTableData {
    TileRange range;
    TileTableDesc desc;
} TileTableData;

typedef struct AvatarPoint {
    fx32 x;
    fx32 y;
} AvatarPoint;

typedef struct AvatarView {
    AvatarPoint position;
    AvatarPoint anchor;
    u8 pad_10[8];
    ProfileBlock *profile;
    u8 pad_1c[0x4aa - 0x1c];
    u8 alpha;
    u8 layer : 2;
    u8 pad_bit2 : 1;
    u8 visible : 1;
    u8 pad_bits : 4;
} AvatarView;

typedef struct PanelState {
    u8 bgMain[0x4c];
    u8 bgSub[0x4c];
    u8 objMain[0x647c];
    u8 objSub[0x647c];
    u8 tileTable[0xc9ac - 0xc990];
    ProfileBlock profile;
    ProfileBlock profileCopy;
    ProfileBlock partnerProfile;
    u8 name[0x67];
    u8 nameCopy[0x67];
    u8 pad_caaa[2];
    AvatarPoint avatarAnchor;
    int handle;
    AvatarView *mainAvatar;
    AvatarView *partnerAvatar;
    u8 pad_cac0[0xcb50 - 0xcac0];
    u8 *categoryTable;
    u8 pad_cb54[0xcf3e - 0xcb54];
    u8 bonusCount;
    u8 pad_cf3f;
    s16 defaultSelection;
    u8 pad_cf42[0xcf76 - 0xcf42];
    s16 rowCount;
    u8 pad_cf78[2];
    s16 columnCount;
    s16 selection;
    s16 pageCount;
    u8 pad_cf80[0xcf8a - 0xcf80];
    s8 focusIndex;
    s8 focusPhase;
    u8 pad_cf8c[0xcf95 - 0xcf8c];
    s8 nextState;
    u8 pad_cf96;
    s8 pendingIndex;
    u8 pad_cf98[4];
} PanelState;

extern PanelState *data_ov014_0206f9a0;
extern BgContainerConfig data_ov014_0206f86c;
extern BgContainerConfig data_ov014_0206f880;
extern ObjManagerConfig data_ov014_0206f894;
extern ObjManagerConfig data_ov014_0206f8ac;
extern char data_ov014_0206f91c[];
extern char data_ov014_0206f92c[];
extern char data_ov014_0206f940[];
extern u16 data_ov014_0206f800[];
extern TileRange data_ov014_0206f8e0;
extern TileTableData TileTableSource_0206f8e0;
extern TileTableDesc data_ov014_0206f8e8;

extern int DispatchContextCommand_02066c78(u32 command, u32 value, u32 extra, void *buffer);
extern void AcquireRecordSlot_02051d3c(int slot, int mode);
extern void *NNSi_FndAllocFromDefaultHeap_0202a178(u32 size);
extern void NNSi_FndFreeFromDefaultHeap_0202a1c4(void *block);
extern void func_01ff8830(void *dst, int value, u32 size);
extern void func_01ff89a8(const void *src, void *dst, u32 size);
extern void func_01ff8740(u32 value, void *dst, u32 size);
extern void BuildPanelGroupEntries_0206f0a0(void);
extern ProfileBlock *func_ov002_02066fc8(void);
extern u8 *func_ov002_02066fb0(void);
extern int func_0202cc6c(const char *path, u32 kind, u32 fromTop);
extern void func_ov002_020629a8(void);
extern void func_ov002_02062768(int value);
extern void *G2S_GetBG3ScrPtr_02007004(void);
extern void GX_SetBankForOBJExtPltt_02008784(int bank);
extern void func_ov027_020b7d58(void *container, BgContainerConfig *config);
extern void func_ov027_020b7e24(void *container, u32 resourceId);
extern void *func_0202c48c(u32 resourceId, u32 kind);
extern void GetBgDataFromArchive_0202b554(BgGraphicsData *out, void *archive, int screenIndex, int characterIndex,
                                          int paletteIndex);
extern void func_02007250(void *data, u32 offset, u32 size);
extern void GX_LoadBG1Char_020079b0(void *data, u32 offset, u32 size);
extern void GX_LoadBG1Scr_02007630(void *data, u32 offset, u32 size);
extern void GX_LoadBG0Char_020078d0(void *data, u32 offset, u32 size);
extern void GX_LoadBG0Scr_02007550(void *data, u32 offset, u32 size);
extern void GXS_LoadBGPltt_020072b4(void *data, u32 offset, u32 size);
extern void GXS_LoadBG1Char_02007a20(void *data, u32 offset, u32 size);
extern void GXS_LoadBG1Scr_020076a0(void *data, u32 offset, u32 size);
extern void GXS_LoadBG0Scr_020075c0(void *data, u32 offset, u32 size);
extern BgEntry *func_ov027_020b8558(void *container, int entryId);
extern void InitializeResourceContainer_020b8bd4(void *container, ObjManagerConfig *config);
extern void InitObjManagerAndMark_020b9060(void *container, ObjManagerConfig *config);
extern void func_ov027_020b9078(void *container, const char *name);
extern void func_ov027_020b8f98(void *container, u32 resourceId, int count);
extern void SetAllElementObjectModes_020b97fc(void *container, int mode);
extern void *func_ov027_020b90a4(void *container, int elementId);
extern void func_ov027_020b9580(void *container, void *element, BOOL visible);
extern void func_ov027_020b95e4(void *container, void *element);
extern void func_ov027_020b96a0(void *container, void *element, u16 frame);
extern void func_ov027_020b97b8(void *container, void *element, int mode);
extern void TallyFlagGroups_0206abc0(u16 *out);
extern void InitTileTableFrom_020b9a0c(void *table, TileTableDesc *source);
extern void *FindLoadedElementById_020b8390(void *container, int id);
extern void SetTagRecordArmed_020b83e8(void *container, void *record, int armed);
extern void func_ov014_0206ec14(void);
extern void LoadAvatarObjPalette_02067b24(BOOL useSubScreen);
extern void ResetSelectionView_02067a84(AvatarView *view);
extern void func_ov002_02067c10(void *container, AvatarView *view);
extern int LookupTableOffset_02069dd8(int table, int index);
extern void SelectCategoryRecord_02067fd8(void *container, AvatarView *view, int record);
extern void SetWidgetRootDpadEnabled_020b9874(void *container, int enabled);
extern void func_ov027_020b9098(void *container, void (*callback)(void));
extern void ResolveEntryStoreWord_020b9088(void *container, int elementId, void (*callback)(void));
extern void CopyPanelEntry_0206e954(void);
extern void func_ov014_0206e9c0(void);
extern void func_ov014_0206e9dc(void);
extern void func_ov014_0206e9f8(void);
extern void func_ov014_0206ea14(void);
extern void func_ov014_0206ea30(void);
extern void ChangePanelState_0206d1c0(int state);

static inline u32 ArchiveFileId(int handle)
{
    return (handle + 0x8000U & 0xfffffc) << 7;
}

static inline void *GetElement(void *container, int id)
{
    return func_ov027_020b90a4(container, id);
}

void InitPanelScene_0206c480(void)
{
    PanelState *mainState;
    u32 fileId;
    PanelState *subState;
    void *digit;
    BgContainerConfig bgMainConfig = data_ov014_0206f86c;
    BgContainerConfig bgSubConfig = data_ov014_0206f880;
    ObjManagerConfig objMainConfig = data_ov014_0206f894;
    u16 tally[4];
    ObjManagerConfig objSubConfig = data_ov014_0206f8ac;
    BgGraphicsData bgData;
    s32 hasRecord;
    s32 id;
    void *archive;
    s32 value;
    PanelState *state;
    void *container;
    void *element;
    BgEntry *entry;
    AvatarView *avatar;
    int handle;

    hasRecord = DispatchContextCommand_02066c78(0xe, 0, 0, 0);
    AcquireRecordSlot_02051d3c(9, 1);
    AcquireRecordSlot_02051d3c(10, 1);
    data_ov014_0206f9a0 = NNSi_FndAllocFromDefaultHeap_0202a178(sizeof(PanelState));
    func_01ff8830(data_ov014_0206f9a0, 0, sizeof(PanelState));
    data_ov014_0206f9a0->focusIndex = -1;
    data_ov014_0206f9a0->focusPhase = 0;
    BuildPanelGroupEntries_0206f0a0();
    data_ov014_0206f9a0->rowCount = 4;
    data_ov014_0206f9a0->columnCount = 6;
    data_ov014_0206f9a0->pageCount = 5;
    data_ov014_0206f9a0->selection = data_ov014_0206f9a0->defaultSelection;
    data_ov014_0206f9a0->pendingIndex = -1;
    state = data_ov014_0206f9a0;
    state->profile = *func_ov002_02066fc8();
    state->profileCopy = state->profile;
    func_01ff89a8(func_ov002_02066fb0() + 0x67, state->name, 0x67);
    func_01ff89a8(data_ov014_0206f9a0->name, data_ov014_0206f9a0->nameCopy, 0x67);

    handle = func_0202cc6c(data_ov014_0206f91c, 0x10, 0);
    func_ov002_020629a8();
    func_ov002_02062768(0);
    *(vu16 *)0x0400100e = (u16)((*(vu16 *)0x0400100e & 0x43) | 0x384);
    func_01ff8740(0, G2S_GetBG3ScrPtr_02007004(), 0x800);
    GX_SetBankForOBJExtPltt_02008784(0);
    *(vu32 *)0x04000000 = (*(vu32 *)0x04000000 & ~0x1f00) | 0x1f00;
    *(vu32 *)0x04001000 = (*(vu32 *)0x04001000 & ~0x1f00) | 0x1f00;
    *(vu16 *)0x0400000c = (u16)(*(vu16 *)0x0400000c & ~3);
    *(vu16 *)0x0400000e = (u16)((*(vu16 *)0x0400000e & ~3) | 2);
    *(vu16 *)0x0400100c = (u16)(*(vu16 *)0x0400100c & ~3);
    *(vu16 *)0x0400100e = (u16)(*(vu16 *)0x0400100e & ~3);

    state = data_ov014_0206f9a0;
    func_ov027_020b7d58(state->bgMain, &bgMainConfig);
    fileId = ArchiveFileId(handle);
    func_ov027_020b7e24(state->bgMain, fileId | 0x80000000);
    archive = func_0202c48c(fileId | 0x80000001, 0x10);
    GetBgDataFromArchive_0202b554(&bgData, archive, -1, 0, 0);
    func_02007250(bgData.palette->data, 0, bgData.palette->size);
    GX_LoadBG1Char_020079b0(bgData.character->data, 0, bgData.character->size);
    entry = func_ov027_020b8558(state->bgMain, 0);
    GX_LoadBG1Scr_02007630(entry->screen->data, 0, entry->screen->size);
    GX_LoadBG0Char_020078d0(bgData.character->data, 0, bgData.character->size);
    entry = func_ov027_020b8558(state->bgMain, 1);
    GX_LoadBG0Scr_02007550(entry->screen->data, 0, entry->screen->size);
    objMainConfig.cellResourceId = fileId | 0x80000002;
    mainState = *(PanelState *volatile *)&data_ov014_0206f9a0;
    objMainConfig.animResourceId = fileId | 0x80000003;
    InitializeResourceContainer_020b8bd4(mainState->objMain, NULL);
    InitObjManagerAndMark_020b9060(mainState->objMain, &objMainConfig);
    func_ov027_020b9078(mainState->objMain, data_ov014_0206f92c);
    func_ov027_020b8f98(mainState->objMain, objMainConfig.animResourceId, 0x14);
    SetAllElementObjectModes_020b97fc(mainState->objMain, 1);
    element = func_ov027_020b90a4(mainState->objMain, 3);
    func_ov027_020b95e4(mainState->objMain, element);
    func_ov027_020b96a0(mainState->objMain, element, 0);
    TallyFlagGroups_0206abc0(tally);
    tally[3] += data_ov014_0206f9a0->bonusCount;
    for (id = 10; id <= 0x19; id++) {
        value = tally[(id - 10) >> 2] * 100 / data_ov014_0206f800[(id - 10) >> 2];
        digit = GetElement(mainState->objMain, id);
        func_ov027_020b9580(mainState->objMain, digit, 1);
        func_ov027_020b95e4(mainState->objMain, digit);
        switch ((id - 10) & 3) {
        case 0:
            continue;
        case 1:
            value = value % 10;
            break;
        case 2:
            value = value / 10;
            if (0 == value) {
                func_ov027_020b9580(mainState->objMain, digit, 0);
                continue;
            }
            if (value >= 10) {
                value = 0;
            }
            break;
        case 3:
            value = value / 100;
            if (value == 0) {
                func_ov027_020b9580(mainState->objMain, digit, 0);
                continue;
            }
            break;
        }
        func_ov027_020b96a0(mainState->objMain, digit, value);
    }
    NNSi_FndFreeFromDefaultHeap_0202a1c4(archive);

    TileTableSource_0206f8e0.desc.range = &data_ov014_0206f8e0;
    InitTileTableFrom_020b9a0c(data_ov014_0206f9a0->tileTable, &data_ov014_0206f8e8);
    subState = data_ov014_0206f9a0;
    func_ov027_020b7d58(subState->bgSub, &bgSubConfig);
    func_ov027_020b7e24(subState->bgSub, fileId | 0x80000004);
    archive = func_0202c48c(fileId | 0x80000005, 0x10);
    GetBgDataFromArchive_0202b554(&bgData, archive, -1, 0, 0);
    GXS_LoadBGPltt_020072b4(bgData.palette->data, 0, bgData.palette->size);
    GXS_LoadBG1Char_02007a20(bgData.character->data, 0, bgData.character->size);
    entry = func_ov027_020b8558(subState->bgSub, 1);
    GXS_LoadBG1Scr_020076a0(entry->screen->data, 0, entry->screen->size);
    entry = func_ov027_020b8558(subState->bgSub, 0);
    GXS_LoadBG0Scr_020075c0(entry->screen->data, 0, entry->screen->size);
    SetTagRecordArmed_020b83e8(subState->bgSub, FindLoadedElementById_020b8390(subState->bgSub, 0), 1);
    SetTagRecordArmed_020b83e8(subState->bgSub, FindLoadedElementById_020b8390(subState->bgSub, 1), 1);
    container = data_ov014_0206f9a0->objSub;
    objSubConfig.cellResourceId = fileId | 0x80000006;
    objSubConfig.animResourceId = fileId | 0x80000007;
    InitializeResourceContainer_020b8bd4(container, NULL);
    InitObjManagerAndMark_020b9060(container, &objSubConfig);
    func_ov027_020b9078(container, data_ov014_0206f940);
    func_ov027_020b8f98(container, objSubConfig.animResourceId, 8);
    SetAllElementObjectModes_020b97fc(container, 1);

    element = func_ov027_020b90a4(container, 1);
    if (!hasRecord) {
        func_ov027_020b95e4(container, element);
    }
    func_ov027_020b9580(container, element, 1);
    element = func_ov027_020b90a4(container, 5);
    func_ov027_020b97b8(container, element, 1);
    if (!hasRecord) {
        func_ov027_020b95e4(container, element);
    }
    func_ov027_020b9580(container, element, 1);
    element = func_ov027_020b90a4(container, 3);
    func_ov027_020b97b8(container, element, 1);
    if (!hasRecord) {
        func_ov027_020b95e4(container, element);
    }
    func_ov027_020b9580(container, element, 1);
    element = func_ov027_020b90a4(container, 4);
    func_ov027_020b97b8(container, element, 1);
    if (!hasRecord) {
        func_ov027_020b95e4(container, element);
    }
    func_ov027_020b9580(container, element, 1);
    element = func_ov027_020b90a4(container, 6);
    func_ov027_020b97b8(container, element, 1);
    if (!hasRecord) {
        func_ov027_020b95e4(container, element);
    }
    func_ov027_020b9580(container, element, 1);
    element = func_ov027_020b90a4(container, 7);
    func_ov027_020b97b8(container, element, 1);
    func_ov027_020b95e4(container, element);
    element = func_ov027_020b90a4(container, 8);
    func_ov027_020b97b8(container, element, 1);
    func_ov027_020b95e4(container, element);
    func_ov014_0206ec14();
    LoadAvatarObjPalette_02067b24(TRUE);

    avatar = NNSi_FndAllocFromDefaultHeap_0202a178(sizeof(AvatarView));
    func_01ff8830(avatar, 0, sizeof(AvatarView));
    avatar->profile = &data_ov014_0206f9a0->profile;
    ResetSelectionView_02067a84(avatar);
    avatar->alpha = 200;
    avatar->layer = 1;
    avatar->visible = 1;
    avatar->position.x = 0xb8000;
    avatar->position.y = 0x52000;
    func_ov002_02067c10(container, avatar);
    data_ov014_0206f9a0->mainAvatar = avatar;

    avatar = NNSi_FndAllocFromDefaultHeap_0202a178(sizeof(AvatarView));
    func_01ff8830(avatar, 0, sizeof(AvatarView));
    avatar->profile = &data_ov014_0206f9a0->partnerProfile;
    avatar->alpha = 100;
    avatar->layer = 1;
    avatar->position.x = 0x3f000;
    avatar->position.y = 0x4e000;
    avatar->visible = 1;
    SelectCategoryRecord_02067fd8(container, avatar,
                                  LookupTableOffset_02069dd8(0, data_ov014_0206f9a0->categoryTable[data_ov014_0206f9a0->selection]));
    data_ov014_0206f9a0->partnerAvatar = avatar;
    data_ov014_0206f9a0->avatarAnchor = avatar->anchor;
    SetWidgetRootDpadEnabled_020b9874(container, 1);
    func_ov027_020b9098(container, CopyPanelEntry_0206e954);
    ResolveEntryStoreWord_020b9088(container, 1, func_ov014_0206e9c0);
    ResolveEntryStoreWord_020b9088(container, 3, func_ov014_0206e9dc);
    ResolveEntryStoreWord_020b9088(container, 4, func_ov014_0206e9f8);
    ResolveEntryStoreWord_020b9088(container, 5, func_ov014_0206ea14);
    ResolveEntryStoreWord_020b9088(container, 6, func_ov014_0206ea30);
    NNSi_FndFreeFromDefaultHeap_0202a1c4(archive);
    data_ov014_0206f9a0->handle = handle;
    data_ov014_0206f9a0->nextState = -5;
    ChangePanelState_0206d1c0(0);
}
