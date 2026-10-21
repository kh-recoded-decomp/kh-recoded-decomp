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

typedef struct CardHeader {
    u32 words[4];
} CardHeader;

typedef struct AvatarFlags {
    u8 layer : 2;
    u8 pad2 : 1;
    u8 framed : 1;
    u8 pad4_7 : 4;
} AvatarFlags;

typedef struct Vec2Fx32 {
    fx32 x;
    fx32 y;
} Vec2Fx32;

typedef struct AvatarView {
    Vec2Fx32 pos;
    Vec2Fx32 cardOffset;
    u8 pad_10[8];
    CardHeader *card;
    u8 pad_1c[0x4aa - 0x1c];
    u8 alpha;
    AvatarFlags flags;
} AvatarView;

typedef struct TileTableSource {
    const int *ids;
    int count;
    u16 width;
    u16 height;
    int rowOffset;
} TileTableSource;

typedef struct BgContainer {
    u8 reserved[0x4c];
} BgContainer;

/* Each container owns image entries, animation slots and widget records. */
typedef struct PanelObjects {
    u8 reserved[0x647c];
} PanelObjects;

typedef struct RecordFlagSets {
    u8 primaryBits[0x67];
    u8 secondaryBits[0x67];
} RecordFlagSets;

typedef struct PanelState {
    BgContainer mainBg;
    BgContainer subBg;
    PanelObjects mainObjects;
    PanelObjects subObjects;
    u8 tiles[0x1c];
    CardHeader card;
    CardHeader savedCard;
    CardHeader shownCard;
    RecordFlagSets flags;
    u8 pad_caaa[2];
    Vec2Fx32 shownCardOffset;
    u32 messageHandle;
    AvatarView *playerView;
    AvatarView *shownView;
    u8 pad_cac0[0xcb50 - 0xcac0];
    u8 *groupEntries[0x14];
    u8 pad_cba0[0xcf3e - 0xcba0];
    u8 bonusCount;
    u8 pad_cf3f;
    s16 firstSelection;
    u8 pad_cf42[0xcf76 - 0xcf42];
    s16 columns;
    s16 index;
    s16 groupWidth;
    s16 selection;
    s16 count;
    u8 pad_cf80[0xcf8a - 0xcf80];
    s8 stateIndex;
    s8 closeRequested;
    s8 step;
    u8 pad_cf8d[0xcf95 - 0xcf8d];
    s8 introTimer;
    u8 pad_cf96;
    s8 hoverIndex;
    u8 pad_cf98[4];
} PanelState;

extern PanelState *data_ov014_0206f9a0;
extern const BgContainerConfig data_ov014_0206f86c;
extern const BgContainerConfig data_ov014_0206f880;
extern const ObjManagerConfig data_ov014_0206f894;
extern const ObjManagerConfig data_ov014_0206f8ac;
extern const u16 data_ov014_0206f800[4];
extern const char sOv014_WxcWldLanguageP2_0206f91c[];
extern const char sOv014_WxcWldl1LanguagePobjZ_0206f92c[];
extern const char sOv014_WxcWldu1LanguagePobjZ_0206f940[];

extern int DispatchContextCommand(u32 command, int value, int extra, void *buffer);
extern int AcquireRecordSlot(int slot, int param);
extern void *NNSi_FndAllocFromDefaultHeap(u32 size);
extern void NNSi_FndFreeFromDefaultHeap(void *memory);
extern void MI_CpuFill8(void *dst, u8 value, u32 size);
extern void MI_CpuCopy8(const void *src, void *dst, u32 size);
extern void MIi_CpuClearFast(u32 value, void *dst, u32 size);
extern void BuildPanelGroupEntries(void);
extern const CardHeader *GetPackedFields(void);
extern const u8 *GetRecordFlagBits(void);
extern u32 Msg_OpenContainerAndReadHeader(const char *path, u32 heapId, u32 flags);
extern void func_ov002_020629a8(void);
extern void ReleasePanelObjectList(int mode);
extern void *G2S_GetBG3ScrPtr(void);
extern void GX_SetBankForOBJExtPltt(int bank);
extern void InitBackgroundContainer(void *container, const BgContainerConfig *config);
extern void func_ov027_020b7e44(void *container, u32 fileId);
extern void *func_0202c4a0(u32 fileId, u32 heapId);
extern void GetBgDataFromArchive(BgGraphicsData *out, void *archive, int screenIndex, int characterIndex,
                                 int paletteIndex);
extern void GX_LoadBGPltt(const void *src, u32 offset, u32 size);
extern void GX_LoadBG0Char(const void *src, u32 offset, u32 size);
extern void GX_LoadBG1Char(const void *src, u32 offset, u32 size);
extern void GX_LoadBG0Scr(const void *src, u32 offset, u32 size);
extern void GX_LoadBG1Scr(const void *src, u32 offset, u32 size);
extern void GXS_LoadBGPltt(const void *src, u32 offset, u32 size);
extern void GXS_LoadBG1Char(const void *src, u32 offset, u32 size);
extern void GXS_LoadBG0Scr(const void *src, u32 offset, u32 size);
extern void GXS_LoadBG1Scr(const void *src, u32 offset, u32 size);
extern BgEntry *func_ov027_020b8578(void *container, int entryId);
extern int InitializeResourceContainer(void *container, void *config);
extern void InitObjManagerAndMark(void *container, ObjManagerConfig *config);
extern void func_ov027_020b9098(void *container, const char *path);
extern void func_ov027_020b8fb8(void *container, u32 fileId, int count);
extern void SetAllElementObjectModes(void *container, int mode);
extern void *FindWidgetById(void *container, int id);
extern void func_ov027_020b9604(void *container, void *widget);
extern void func_ov027_020b96c0(void *container, void *widget, u16 frame);
extern void func_ov027_020b97d8(void *container, void *widget, int mode);
extern void SetEntrySlotsVisible(void *container, void *widget, int visible);
extern void TallyFlagGroups(u16 *counts);
extern void InitTileTableFrom(void *tiles, const TileTableSource *source);
extern void *FindLoadedElementById(void *container, int id);
extern void SetTagRecordArmed(void *container, void *record, int armed);
extern void RefreshPanelCategorySlots(void);
extern void LoadAvatarObjPalette(BOOL subScreen);
extern void ResetSelectionView(AvatarView *view);
extern void BuildSelectionViewRecords(void *container, AvatarView *view);
extern u32 LookupTableOffset(s32 category, u32 entry);
extern void SelectCategoryRecord(void *container, AvatarView *view, u32 record);
extern void SetWidgetRootDpadEnabled(void *container, int enabled);
extern void func_ov027_020b90b8(void *container, void (*callback)(void));
extern void func_ov027_020b90a8(void *container, int elementId, void (*callback)(void));
extern void ChangePanelState(int state);
extern void CopyPanelEntry(void);
extern void SetPanelInfoMode2(void);
extern void SetPanelInfoMode16(void);
extern void SetPanelInfoMode32(void);
extern void SetPanelInfoMode64(void);
extern void SetPanelInfoMode128(void);

#pragma explicit_zero_data on

/* The tile table InitTileTableFrom builds for the sub screen; its id list is linked in at run time. */
TileTableSource gRecordPanelTileSource = { NULL, 1, 32, 24, 0 };
int gRecordPanelTileIds[2] = { 0x18, 0x18 };

#pragma explicit_zero_data off

#define REG_DISPCNT (*(vu32 *)0x04000000)
#define REG_BG2CNT (*(vu16 *)0x0400000c)
#define REG_BG3CNT (*(vu16 *)0x0400000e)
#define REG_DB_DISPCNT (*(vu32 *)0x04001000)
#define REG_DB_BG2CNT (*(vu16 *)0x0400100c)
#define REG_DB_BG3CNT (*(vu16 *)0x0400100e)

/* Opens the record panel: both screens' backgrounds, the completion percentages of the four record
 * groups, the category widgets and the two avatar cards. ShutdownPanelObjects tears it down. */
void InitRecordPanel(void)
{
    BgContainerConfig mainBgConfig = data_ov014_0206f86c;
    BgContainerConfig subBgConfig = data_ov014_0206f880;
    ObjManagerConfig mainObjConfig = data_ov014_0206f894;
    ObjManagerConfig subObjConfig = data_ov014_0206f8ac;
    BgGraphicsData bgData;
    u16 counts[4];
    int i;
    PanelState *state;
    BgContainer *subBg;
    AvatarView *view;
    int busy;
    void *widget;
    BgEntry *entry;
    int percent;
    void *archive;
    PanelObjects *objects;
    u32 resourceBase;
    u32 handle;

    busy = DispatchContextCommand(0xe, 0, 0, NULL);
    AcquireRecordSlot(9, 1);
    AcquireRecordSlot(10, 1);
    data_ov014_0206f9a0 = NNSi_FndAllocFromDefaultHeap(sizeof(PanelState));
    MI_CpuFill8(data_ov014_0206f9a0, 0, sizeof(PanelState));
    data_ov014_0206f9a0->stateIndex = -1;
    data_ov014_0206f9a0->closeRequested = 0;
    BuildPanelGroupEntries();
    data_ov014_0206f9a0->columns = 4;
    data_ov014_0206f9a0->groupWidth = 6;
    data_ov014_0206f9a0->count = 5;
    data_ov014_0206f9a0->selection = data_ov014_0206f9a0->firstSelection;
    data_ov014_0206f9a0->hoverIndex = -1;
    state = data_ov014_0206f9a0;
    state->card = *GetPackedFields();
    state->savedCard = state->card;
    MI_CpuCopy8(GetRecordFlagBits() + 0x67, state->flags.primaryBits, 0x67);
    MI_CpuCopy8(data_ov014_0206f9a0->flags.primaryBits, data_ov014_0206f9a0->flags.secondaryBits, 0x67);
    handle = Msg_OpenContainerAndReadHeader(sOv014_WxcWldLanguageP2_0206f91c, 0x10, 0);
    func_ov002_020629a8();
    ReleasePanelObjectList(0);
    REG_DB_BG3CNT = (REG_DB_BG3CNT & 0x43) | 0x384;
    MIi_CpuClearFast(0, G2S_GetBG3ScrPtr(), 0x800);
    GX_SetBankForOBJExtPltt(0);
    REG_DISPCNT = (REG_DISPCNT & ~0x1f00) | 0x1f00;
    REG_DB_DISPCNT = (REG_DB_DISPCNT & ~0x1f00) | 0x1f00;
    REG_BG2CNT = REG_BG2CNT & ~3;
    REG_BG3CNT = (REG_BG3CNT & ~3) | 2;
    REG_DB_BG2CNT = REG_DB_BG2CNT & ~3;
    REG_DB_BG3CNT = REG_DB_BG3CNT & ~3;

    state = data_ov014_0206f9a0;
    InitBackgroundContainer(&state->mainBg, &mainBgConfig);
    resourceBase = (handle + 0x8000 & 0xfffffc) << 7;
    func_ov027_020b7e44(&state->mainBg, resourceBase | 0x80000000);
    archive = func_0202c4a0(resourceBase | 0x80000001, 0x10);
    GetBgDataFromArchive(&bgData, archive, -1, 0, 0);
    GX_LoadBGPltt(bgData.palette->data, 0, bgData.palette->size);
    GX_LoadBG1Char(bgData.character->data, 0, bgData.character->size);
    entry = func_ov027_020b8578(&state->mainBg, 0);
    GX_LoadBG1Scr(entry->screen->data, 0, entry->screen->size);
    GX_LoadBG0Char(bgData.character->data, 0, bgData.character->size);
    entry = func_ov027_020b8578(&state->mainBg, 1);
    GX_LoadBG0Scr(entry->screen->data, 0, entry->screen->size);

    state = data_ov014_0206f9a0;
    objects = &state->mainObjects;
    mainObjConfig.cellResourceId = resourceBase | 0x80000002;
    mainObjConfig.animResourceId = resourceBase | 0x80000003;
    InitializeResourceContainer(objects, NULL);
    InitObjManagerAndMark(objects, &mainObjConfig);
    func_ov027_020b9098(objects, sOv014_WxcWldl1LanguagePobjZ_0206f92c);
    func_ov027_020b8fb8(objects, mainObjConfig.animResourceId, 0x14);
    SetAllElementObjectModes(objects, 1);
    widget = FindWidgetById(objects, 3);
    func_ov027_020b9604(objects, widget);
    func_ov027_020b96c0(objects, widget, 0);

    TallyFlagGroups(counts);
    counts[3] += data_ov014_0206f9a0->bonusCount;
    for (i = 10; i <= 0x19; i++) {
        int group = (i - 10) >> 2;

        percent = counts[group] * 100 / data_ov014_0206f800[group];
        widget = FindWidgetById(objects, i);
        SetEntrySlotsVisible(objects, widget, 1);
        func_ov027_020b9604(objects, widget);
        switch ((i - 10) & 3) {
        case 0:
            continue;
        case 1:
            percent %= 10;
            break;
        case 2:
            percent /= 10;
            if (percent == 0) {
                SetEntrySlotsVisible(objects, widget, 0);
                continue;
            }
            if (percent >= 10) {
                percent = 0;
            }
            break;
        case 3:
            percent /= 100;
            if (percent == 0) {
                SetEntrySlotsVisible(objects, widget, 0);
                continue;
            }
            break;
        }
        func_ov027_020b96c0(objects, widget, percent);
    }
    NNSi_FndFreeFromDefaultHeap(archive);

    gRecordPanelTileSource.ids = gRecordPanelTileIds;
    InitTileTableFrom(data_ov014_0206f9a0->tiles, &gRecordPanelTileSource);
    subBg = &data_ov014_0206f9a0->subBg;
    InitBackgroundContainer(subBg, &subBgConfig);
    func_ov027_020b7e44(subBg, resourceBase | 0x80000004);
    archive = func_0202c4a0(resourceBase | 0x80000005, 0x10);
    GetBgDataFromArchive(&bgData, archive, -1, 0, 0);
    GXS_LoadBGPltt(bgData.palette->data, 0, bgData.palette->size);
    GXS_LoadBG1Char(bgData.character->data, 0, bgData.character->size);
    entry = func_ov027_020b8578(subBg, 1);
    GXS_LoadBG1Scr(entry->screen->data, 0, entry->screen->size);
    entry = func_ov027_020b8578(subBg, 0);
    GXS_LoadBG0Scr(entry->screen->data, 0, entry->screen->size);
    SetTagRecordArmed(subBg, FindLoadedElementById(subBg, 0), 1);
    SetTagRecordArmed(subBg, FindLoadedElementById(subBg, 1), 1);

    objects = &data_ov014_0206f9a0->subObjects;
    subObjConfig.cellResourceId = resourceBase | 0x80000006;
    subObjConfig.animResourceId = resourceBase | 0x80000007;
    InitializeResourceContainer(objects, NULL);
    InitObjManagerAndMark(objects, &subObjConfig);
    func_ov027_020b9098(objects, sOv014_WxcWldu1LanguagePobjZ_0206f940);
    func_ov027_020b8fb8(objects, subObjConfig.animResourceId, 8);
    SetAllElementObjectModes(objects, 1);
    widget = FindWidgetById(objects, 1);
    if (!busy) {
        func_ov027_020b9604(objects, widget);
    }
    SetEntrySlotsVisible(objects, widget, 1);
    widget = FindWidgetById(objects, 5);
    func_ov027_020b97d8(objects, widget, 1);
    if (!busy) {
        func_ov027_020b9604(objects, widget);
    }
    SetEntrySlotsVisible(objects, widget, 1);
    widget = FindWidgetById(objects, 3);
    func_ov027_020b97d8(objects, widget, 1);
    if (!busy) {
        func_ov027_020b9604(objects, widget);
    }
    SetEntrySlotsVisible(objects, widget, 1);
    widget = FindWidgetById(objects, 4);
    func_ov027_020b97d8(objects, widget, 1);
    if (!busy) {
        func_ov027_020b9604(objects, widget);
    }
    SetEntrySlotsVisible(objects, widget, 1);
    widget = FindWidgetById(objects, 6);
    func_ov027_020b97d8(objects, widget, 1);
    if (!busy) {
        func_ov027_020b9604(objects, widget);
    }
    SetEntrySlotsVisible(objects, widget, 1);
    widget = FindWidgetById(objects, 7);
    func_ov027_020b97d8(objects, widget, 1);
    func_ov027_020b9604(objects, widget);
    widget = FindWidgetById(objects, 8);
    func_ov027_020b97d8(objects, widget, 1);
    func_ov027_020b9604(objects, widget);
    RefreshPanelCategorySlots();
    LoadAvatarObjPalette(TRUE);

    view = NNSi_FndAllocFromDefaultHeap(sizeof(AvatarView));
    MI_CpuFill8(view, 0, sizeof(AvatarView));
    view->card = &data_ov014_0206f9a0->card;
    ResetSelectionView(view);
    view->alpha = 200;
    view->flags.layer = 1;
    view->flags.framed = 1;
    view->pos.x = 0xb8000;
    view->pos.y = 0x52000;
    BuildSelectionViewRecords(objects, view);
    data_ov014_0206f9a0->playerView = view;

    view = NNSi_FndAllocFromDefaultHeap(sizeof(AvatarView));
    MI_CpuFill8(view, 0, sizeof(AvatarView));
    view->card = &data_ov014_0206f9a0->shownCard;
    view->alpha = 100;
    view->flags.layer = 1;
    view->pos.x = 0x3f000;
    view->pos.y = 0x4e000;
    view->flags.framed = 1;
    SelectCategoryRecord(objects, view,
                         LookupTableOffset(0, data_ov014_0206f9a0->groupEntries[0][data_ov014_0206f9a0->selection]));
    data_ov014_0206f9a0->shownView = view;
    data_ov014_0206f9a0->shownCardOffset = view->cardOffset;
    SetWidgetRootDpadEnabled(objects, 1);
    func_ov027_020b90b8(objects, CopyPanelEntry);
    func_ov027_020b90a8(objects, 1, SetPanelInfoMode2);
    func_ov027_020b90a8(objects, 3, SetPanelInfoMode16);
    func_ov027_020b90a8(objects, 4, SetPanelInfoMode32);
    func_ov027_020b90a8(objects, 5, SetPanelInfoMode64);
    func_ov027_020b90a8(objects, 6, SetPanelInfoMode128);
    NNSi_FndFreeFromDefaultHeap(archive);
    data_ov014_0206f9a0->messageHandle = handle;
    data_ov014_0206f9a0->introTimer = -5;
    ChangePanelState(0);
}
