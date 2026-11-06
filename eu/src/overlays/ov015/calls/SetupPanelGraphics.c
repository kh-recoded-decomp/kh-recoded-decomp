#include "src/overlays/ov027/WidgetRecordOps.h"
#include "nitro/types.h"
#include "src/overlays/ov015/WirelessBoardData.h"
#include "nitro/fx_types.h"
#include "src/overlays/ov015/WirelessPanelInitData.h"
#include "src/overlays/ov002/RecordSelectionView.h"
#include "src/overlays/ov027/WidgetPosition.h"

typedef WirelessPanelBgConfig BgContainerConfig;

typedef WirelessPanelObjConfig ObjManagerConfig;

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

typedef WidgetPoint ElementPosition;

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
    RecordSelectionView avatarView;
    u8 mainBg[0x4c];
    u8 subBg[0x4c];
    u8 mainObj[0x647c];
    u8 subObj[0x647c];
    u8 pad_CF3C[0xcf48 - 0xcf3c];
    ProfileBlock profileCopy;
} PanelState;

extern PanelState *gWirelessMenuWork;
extern u32 gLinkPanelAssetPaths[];
extern const char sOv015_WxcWlmP2_0207e7e0[];
extern const char sOv015_WxcWlaP2_0207e7ec[];

extern void HandleWirelessPanelNavigation(WidgetPositionRecord *widget, u32 keys);
extern void WirelessSubWidget4ConfirmNoop(void);
extern void PositionWirelessPanelSelectionMarker(void);
extern void SetPanelFlagE2Bit3(void);
extern void SelectPreviousWirelessPanelSubpageWrapper(void);
extern void SelectNextWirelessPanelSubpageWrapper(void);
extern void SelectPreviousWirelessPanelPageWrapper(void);
extern void SelectNextWirelessPanelPageWrapper(void);

extern void ReleaseWirelessMenuWidgetGroups(void);
extern void GX_SetBankForSubOBJExtPltt(int bank);
extern void GX_SetBankForOBJExtPltt(int bank);
extern void ResetOv002PanelGraphics(void);
extern int Msg_OpenContainerAndReadHeader(const char *name, u32 mode, BOOL allocFromEnd);
extern void ZeroHalfThenFree(int handle);
extern void *LoadFileAllocFromHeapTail(u32 fileId, u32 type);
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
extern u16 NextSharedRandom16Scaled(u16 range);

extern void InitBackgroundContainer(void *container, const BgContainerConfig *config);
extern void LoadTagTrackerResourceFile(void *container, u32 fileId);
extern BgScreenEntry *FindActiveBackgroundScreenResourceById(void *container, int entryId);
extern BgScreenRecord *FindActiveRecordById(void *container, u32 recordId);
extern int InitializeResourceContainer(void *container, void *config);
extern void InitObjManagerAndMark(void *container, ObjManagerConfig *config);
extern void CreateWidgetImageEntry(void *container, u32 value);
extern void LoadWidgetDescriptorsFromFile(void *container, u32 fileId, int count);
extern void SetAllElementObjectModes(void *container, int mode);
extern void *FindWidgetById(void *container, int elementId);
extern void SetEntrySlotsVisible(void *container, void *element, BOOL enabled);
extern void SetFocusedWidget(void *container, void *element);
extern void SetWidgetRootDpadEnabled(void *container, int value);
extern void SetWidgetRootTouchEnabled(void *container, int value);
extern void SetWidgetRootInputCallback(void *container,
                             void (*callback)(WidgetPositionRecord *widget, u32 keys));
extern void ResolveEntryStoreWord(void *container, int elementId, void (*callback)(void));

extern int DispatchContextCommand(int query, int arg1, int arg2, int arg3);
extern int CountSetFlagsInRange(void);
extern ProfileBlock *GetPackedFields(void);
extern void LoadAvatarObjPalette(BOOL useSubScreen);
extern void ResetSelectionView(RecordSelectionView *view);
extern void SetGroupSlotsVisible(void *container, RecordSelectionView *view, int mode);

static inline void SetElementEnabled(void *container, int elementId, BOOL enabled) {
    SetEntrySlotsVisible(container, FindWidgetById(container, elementId), enabled);
}

static inline void SetElementMode(void *container, int elementId, int mode) {
    SetWidgetRecordMode(container, (const struct WidgetPositionRecord *)(FindWidgetById(container, elementId)), mode);
}

static inline void GetElementPosition(void *container, int elementId, ElementPosition *position) {
    ResolveWidgetPositionComponents(container, FindWidgetById(container, elementId), position, 0);
}

static inline void SetElementPosition(void *container, int elementId, ElementPosition *position) {
    SetWidgetPosition(container, FindWidgetById(container, elementId), position, 0);
}

static inline void ClearElementNumber(void *container, int elementId) {
    ClearWidgetRecordActiveBits(container, (const struct WidgetPositionRecord *)(FindWidgetById(container, elementId)));
}

static inline void SetElementNumber(void *container, int elementId, u16 value) {
    SetWidgetAnimationFrame(container, (const struct WidgetPositionRecord *)(FindWidgetById(container, elementId)), (u16)(value));
}

void SetupPanelGraphics(void) {
    BgContainerConfig mainBgConfig = gWirelessMainBgConfig;
    ObjManagerConfig mainObjConfig = gWirelessMainObjConfig;
    BgContainerConfig subBgConfig = gWirelessSubBgConfig;
    ObjManagerConfig subObjConfig = gWirelessSubObjConfig;
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

    gWirelessMenuWork->flagE1Bit3 = 0;
    gWirelessMenuWork->flagE2Bit1 = 0;
    gWirelessMenuWork->flagE1Bit4 = 0;
    gWirelessMenuWork->flagE1Bit7 = 0;
    gWirelessMenuWork->flagE1Mode = 0;
    ReleaseWirelessMenuWidgetGroups();
    gWirelessMenuWork->mainLoaded = 1;
    gWirelessMenuWork->subLoaded = 1;
    GX_SetBankForSubOBJExtPltt(0x100);
    GX_SetBankForOBJExtPltt(0);
    *(vu32 *)0x4000000 = (*(vu32 *)0x4000000 & ~0x1f00) | 0x1f00;
    *(vu32 *)0x4001000 = (*(vu32 *)0x4001000 & ~0x1f00) | 0x1e00;
    ResetOv002PanelGraphics();

    handle = Msg_OpenContainerAndReadHeader(sOv015_WxcWlmP2_0207e7e0, 0x10, 0);
    fileId = ((handle + 0x8000) & 0xfffffc) << 7;
    mainObjConfig.cellFileId = fileId | 0x80000002;
    mainObjConfig.animFileId = fileId | 0x80000003;
    InitBackgroundContainer(gWirelessMenuWork->mainBg, &mainBgConfig);
    LoadTagTrackerResourceFile(gWirelessMenuWork->mainBg, fileId | 0x80000000);
    archive = LoadFileAllocFromHeapTail(fileId | 0x80000001, 0x10);
    GetBgDataFromArchive(&bgData, archive, -1, 0, 0);
    GX_LoadBGPltt(bgData.palette->rawData, 0, bgData.palette->size);
    GX_LoadBG1Char(bgData.character->rawData, 0, bgData.character->size);
    entry = FindActiveBackgroundScreenResourceById(gWirelessMenuWork->mainBg, 0);
    GX_LoadBG1Scr(entry->screen->rawData, 0, entry->screen->size);
    entry = FindActiveBackgroundScreenResourceById(gWirelessMenuWork->mainBg, 1);
    GX_LoadBG0Scr(entry->screen->rawData,
                           FindActiveRecordById(gWirelessMenuWork->mainBg, 1)->charOffset << 6,
                           entry->screen->size);
    InitializeResourceContainer(gWirelessMenuWork->mainObj, NULL);
    InitObjManagerAndMark(gWirelessMenuWork->mainObj, &mainObjConfig);
    CreateWidgetImageEntry(gWirelessMenuWork->mainObj, gLinkPanelAssetPaths[1]);
    LoadWidgetDescriptorsFromFile(gWirelessMenuWork->mainObj, mainObjConfig.animFileId, 0x14);
    SetAllElementObjectModes(gWirelessMenuWork->mainObj, 3);
    SetElementEnabled(gWirelessMenuWork->mainObj, 4, 0);
    SetElementEnabled(gWirelessMenuWork->mainObj, 5, 0);
    SetElementEnabled(gWirelessMenuWork->mainObj, 6, 0);
    SetElementEnabled(gWirelessMenuWork->mainObj, 7, 0);
    SetElementEnabled(gWirelessMenuWork->mainObj, 8, 0);
    SetElementEnabled(gWirelessMenuWork->mainObj, 9, 0);
    SetElementEnabled(gWirelessMenuWork->mainObj, 10, 0);
    SetElementEnabled(gWirelessMenuWork->mainObj, 11, 0);
    SetElementEnabled(gWirelessMenuWork->mainObj, 12, 0);
    SetElementEnabled(gWirelessMenuWork->mainObj, 13, 0);
    SetElementEnabled(gWirelessMenuWork->mainObj, 14, 0);
    SetElementEnabled(gWirelessMenuWork->mainObj, 15, 0);
    SetElementEnabled(gWirelessMenuWork->mainObj, 16, 0);
    SetElementEnabled(gWirelessMenuWork->mainObj, 17, 0);
    SetElementEnabled(gWirelessMenuWork->mainObj, 18, 0);
    NNSi_FndFreeFromDefaultHeap(archive);
    ZeroHalfThenFree(handle);

    handle = Msg_OpenContainerAndReadHeader(sOv015_WxcWlaP2_0207e7ec, 0x10, 0);
    InitBackgroundContainer(gWirelessMenuWork->subBg, &subBgConfig);
    fileId = ((handle + 0x8000) & 0xfffffc) << 7;
    LoadTagTrackerResourceFile(gWirelessMenuWork->subBg, fileId | 0x80000000);
    archive = LoadFileAllocFromHeapTail(fileId | 0x80000002, 0x10);
    GetBgDataFromArchive(&bgData, archive, -1, 0, 0);
    GXS_LoadBGPltt(bgData.palette->rawData, 0, bgData.palette->size);
    GXS_LoadBG1Char(bgData.character->rawData, 0, bgData.character->size);
    entry = FindActiveBackgroundScreenResourceById(gWirelessMenuWork->subBg, 0);
    GXS_LoadBG1Scr(entry->screen->rawData, 0, entry->screen->size);
    entry = FindActiveBackgroundScreenResourceById(gWirelessMenuWork->subBg, 2);
    GXS_LoadBG0Scr(entry->screen->rawData,
                            FindActiveRecordById(gWirelessMenuWork->subBg, 2)->charOffset << 6,
                            entry->screen->size);
    subObjConfig.cellFileId = fileId | 0x80000004;
    subObjConfig.animFileId = fileId | 0x80000007;
    InitializeResourceContainer(gWirelessMenuWork->subObj, NULL);
    InitObjManagerAndMark(gWirelessMenuWork->subObj, &subObjConfig);
    CreateWidgetImageEntry(gWirelessMenuWork->subObj, gLinkPanelAssetPaths[3]);
    LoadWidgetDescriptorsFromFile(gWirelessMenuWork->subObj, subObjConfig.animFileId, 0x19);
    SetAllElementObjectModes(gWirelessMenuWork->subObj, 3);
    if (DispatchContextCommand(5, 0, 0, 0) != 0) {
        SetElementEnabled(gWirelessMenuWork->subObj, 8, 1);
        SetElementMode(gWirelessMenuWork->subObj, 8, 0);
    }

    level = DispatchContextCommand(8, 0, 0, 0);
    if (DispatchContextCommand(5, 0, 0, 0) != 0) {
        level = 0;
    }
    if (level >= 80) {
        ElementPosition position;
        void *container;
        container = gWirelessMenuWork->subObj;
        SetEntrySlotsVisible(container, FindWidgetById(container, 14), 1);
        container = gWirelessMenuWork->subObj;
        ResolveWidgetPositionComponents(container, FindWidgetById(container, 14), &position, 0);
        *(volatile fx32 *)&position.x = ((position.x >> 12) - 10) << 12;
        container = (*(PanelState *volatile *)&gWirelessMenuWork)->subObj;
        SetWidgetPosition(container, FindWidgetById(container, 14), &position, 0);
    } else if (level >= 50) {
        ElementPosition position;
        void *container;
        container = gWirelessMenuWork->subObj;
        SetEntrySlotsVisible(container, FindWidgetById(container, 13), 1);
        container = gWirelessMenuWork->subObj;
        ResolveWidgetPositionComponents(container, FindWidgetById(container, 13), &position, 0);
        *(volatile fx32 *)&position.x = ((position.x >> 12) - 10) << 12;
        container = (*(PanelState *volatile *)&gWirelessMenuWork)->subObj;
        SetWidgetPosition(container, FindWidgetById(container, 13), &position, 0);
    }
    {
        ElementPosition position;
        GetElementPosition(gWirelessMenuWork->subObj, 10, &position);
        position.x -= 0x19000;
        SetElementPosition(gWirelessMenuWork->subObj, 11, &position);
    }

    LoadAvatarObjPalette(TRUE);
    state = gWirelessMenuWork;
    state->profileCopy = *GetPackedFields();
    state->avatarView.selection = &state->profileCopy;
    ResetSelectionView(&gWirelessMenuWork->avatarView);
    gWirelessMenuWork->avatarView.basePriority = 200;
    gWirelessMenuWork->avatarView.flags.mode = 3;
    gWirelessMenuWork->avatarView.position.x = 0xc6000;
    gWirelessMenuWork->avatarView.position.y = 0x29000;
    BuildSelectionViewRecords(gWirelessMenuWork->subObj,
                               &gWirelessMenuWork->avatarView);
    SetGroupSlotsVisible(gWirelessMenuWork->subObj,
                         &gWirelessMenuWork->avatarView, 1);
    SetWidgetRootDpadEnabled(gWirelessMenuWork->subObj, 1);
    SetWidgetRootTouchEnabled(gWirelessMenuWork->subObj, 1);
    SetElementEnabled(gWirelessMenuWork->subObj, 2, 0);
    SetElementEnabled(gWirelessMenuWork->subObj, 3, 0);
    SetElementEnabled(gWirelessMenuWork->subObj, 9, 1);
    SetElementEnabled(gWirelessMenuWork->subObj, 4, 1);
    SetElementEnabled(gWirelessMenuWork->subObj, 17, 1);
    SetElementMode(gWirelessMenuWork->subObj, 4, 3);
    SetElementEnabled(gWirelessMenuWork->subObj, 30, 1);
    SetElementEnabled(gWirelessMenuWork->subObj, 31, 1);
    SetElementEnabled(gWirelessMenuWork->subObj, 32, 1);
    SetElementEnabled(gWirelessMenuWork->subObj, 33, 1);
    SetElementEnabled(gWirelessMenuWork->subObj, 18, 1);

    count = CountSetFlagsInRange();
    ClearElementNumber(gWirelessMenuWork->subObj, 20);
    ClearElementNumber(gWirelessMenuWork->subObj, 21);
    SetElementNumber(gWirelessMenuWork->subObj, 20, count % 10);
    tens = (count / 10) % 10;
    if (tens != 0) {
        SetElementNumber(gWirelessMenuWork->subObj, 21, tens);
    } else {
        SetElementEnabled(gWirelessMenuWork->subObj, 21, 0);
    }

    gWirelessMenuWork->randomDigit = NextSharedRandom16Scaled(6);
    ClearElementNumber(gWirelessMenuWork->subObj, 10);
    {
        PanelState *panel = gWirelessMenuWork;
        void *container = panel->subObj;
        SetWidgetAnimationFrame(container, (const struct WidgetPositionRecord *)(FindWidgetById(container, 10)), (u16)(panel->randomDigit));
    }
    gWirelessMenuWork->randomPick = NextSharedRandom16Scaled(gWirelessRandomChoiceLimits[DispatchContextCommand(6, 0, 0, 0)]);
    {
        void *element = FindWidgetById(gWirelessMenuWork->subObj, 10);
        SetFocusedWidget(gWirelessMenuWork->subObj, element);
    }
    SetWidgetRootInputCallback(gWirelessMenuWork->subObj, HandleWirelessPanelNavigation);
    ResolveEntryStoreWord(gWirelessMenuWork->subObj, 4, WirelessSubWidget4ConfirmNoop);
    ResolveEntryStoreWord(gWirelessMenuWork->subObj, 9, PositionWirelessPanelSelectionMarker);
    ResolveEntryStoreWord(gWirelessMenuWork->subObj, 17, SetPanelFlagE2Bit3);
    ResolveEntryStoreWord(gWirelessMenuWork->subObj, 30, SelectPreviousWirelessPanelSubpageWrapper);
    ResolveEntryStoreWord(gWirelessMenuWork->subObj, 31, SelectNextWirelessPanelSubpageWrapper);
    ResolveEntryStoreWord(gWirelessMenuWork->subObj, 32, SelectPreviousWirelessPanelPageWrapper);
    ResolveEntryStoreWord(gWirelessMenuWork->subObj, 33, SelectNextWirelessPanelPageWrapper);
    NNSi_FndFreeFromDefaultHeap(archive);
    ZeroHalfThenFree(handle);

    gWirelessMenuWork->flagE1Bit3 = 1;
    gWirelessMenuWork->flagE2Bit1 = 1;
    gWirelessMenuWork->flagE2Bit2 = 1;
    gWirelessMenuWork->flagE1Bit4 = 1;
    if (DispatchContextCommand(5, 0, 0, 0) != 0) {
        gWirelessMenuWork->flagE1Mode = 1;
    }
    gWirelessMenuWork->scaleX = NextSharedRandom16Scaled(0x1000) + 0x1000;
    gWirelessMenuWork->offsetX = NextSharedRandom16Scaled(0);
    gWirelessMenuWork->scaleY = NextSharedRandom16Scaled(0x1000) + 0x1000;
    gWirelessMenuWork->offsetY = (NextSharedRandom16Scaled(0) + 0x80) << 12;
    GXS_BeginLoadOBJExtPltt();
    gWirelessMenuWork->extPaletteColor = *(u16 *)0x068a0002;
    gWirelessMenuWork->extPaletteColorCopy = gWirelessMenuWork->extPaletteColor;
    GXS_EndLoadOBJExtPltt();
}
