#include "src/overlays/ov027/WidgetRecordOps.h"
#include "nitro/types.h"
#include "nitro/fx_types.h"
#include "src/overlays/ov002/RecordSelectionView.h"

/* Background container setup: three layer ids and the two layer callbacks. */
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

typedef struct BgRecord {
    u8 pad_00[4];
    s16 scrollY;
} BgRecord;

typedef struct ObjElement {
    u8 pad_00[0x14];
    s32 animIndex;
} ObjElement;

typedef struct ProfileBlock {
    u32 words[4];
} ProfileBlock;

typedef struct MenuFlags {
    u8 pad0 : 1;
    u8 hasProgress : 1;
    u8 hasCategory : 1;
    u8 hasUnlockedEntry : 1;
    u8 pad4_7 : 4;
} MenuFlags;

typedef struct MenuContext {
    s8 state;
    u8 mode;
    u8 pad_02;
    s8 selectedIndex;
    u8 pad_04[0x10 - 0x04];
    fx32 cloudSpeedX;
    fx32 cloudSpeedY;
    fx32 cloudOffsetX;
    fx32 cloudOffsetY;
    u8 pad_20[2];
    MenuFlags flags;
    u8 pad_23;
    int messageHandle;
    RecordSelectionView selection;
    u8 mainBg[0x4c];
    u8 subBg[0x4c];
    u8 mainObj[0x647c];
    u8 subObj[0x647c];
    u8 fileView[0xc];
    ProfileBlock profileCopy;
} MenuContext;

extern MenuContext *gOv002MenuWork;
extern const BgContainerConfig gOv002MenuMainBgConfig;
extern const BgContainerConfig gOv002MenuSubBgConfig;
extern const ObjManagerConfig gOv002MenuMainObjConfig;
extern const ObjManagerConfig gOv002MenuSubObjConfig;
extern u32 gPanelUiResourcePaths[4];
extern const char sOv002_WxcWlmP2_0206c410[];

extern void InitOv002SubPanelGraphics(void);
extern void *NNSi_FndAllocFromDefaultHeap(u32 size);
extern void MI_CpuFill8(void *dst, u8 value, u32 size);
extern void LoadPackedFileView(void *view, u32 path, BOOL fromTop);
extern int Msg_OpenContainerAndReadHeader(const char *path, u32 kind, u32 fromTop);
extern void GX_SetBankForSubOBJExtPltt(int bank);
extern void GX_SetBankForOBJExtPltt(int bank);
extern void ResetOv002PanelGraphics(void);
extern void InitBackgroundContainer(void *container, const BgContainerConfig *config);
extern void LoadTagTrackerResourceFile(void *container, u32 resourceId);
extern void *LoadFileAllocFromHeapTail(u32 resourceId, u32 kind);
extern void GetBgDataFromArchive(BgGraphicsData *out, void *archive, int screenIndex, int characterIndex,
                                 int paletteIndex);
extern void GX_LoadBGPltt(void *data, u32 offset, u32 size);
extern void GX_LoadBG0Char(void *data, u32 offset, u32 size);
extern void GX_LoadBG0Scr(void *data, u32 offset, u32 size);
extern void GX_LoadBG1Scr(void *data, u32 offset, u32 size);
extern void GXS_LoadBGPltt(void *data, u32 offset, u32 size);
extern void GXS_LoadBG0Char(void *data, u32 offset, u32 size);
extern void GXS_LoadBG0Scr(void *data, u32 offset, u32 size);
extern void GXS_LoadBG1Scr(void *data, u32 offset, u32 size);
extern void NNSi_FndFreeFromDefaultHeap(void *block);
extern BgEntry *FindActiveBackgroundScreenResourceById(void *container, int entryId);
extern BgRecord *FindActiveRecordById(void *container, int id);
extern void InitializeResourceContainer(void *container, ObjManagerConfig *config);
extern void InitObjManagerAndMark(void *container, ObjManagerConfig *config);
extern void CreateWidgetImageEntry(void *container, u32 value);
extern void LoadWidgetDescriptorsFromFile(void *container, u32 resourceId, int count);
extern void SetAllElementObjectModes(void *container, int mode);
extern void *FindWidgetById(void *container, int id);
extern void SetIndexedRecordPriority(void *container, int animIndex, int value);
extern void SetEntrySlotsVisible(void *container, void *element, BOOL visible);
extern BOOL HasAnyMenuEntryUnlocked(void);
extern int GetRecordFlagBits(void);
extern BOOL GetCategoryFlagState(int category, int flag);
extern int DispatchContextCommand(u32 command, int arg1, int arg2, int arg3);
extern void ApplySelectedSubitemValues(void *container, void *element, int useAlt);
extern void LoadAvatarObjPalette(BOOL useSubScreen);
extern ProfileBlock *GetPackedFields(void);
extern void ResetSelectionView(RecordSelectionView *view);
extern void SetGroupSlotsVisible(void *container, RecordSelectionView *view, BOOL visible);
extern void SetWidgetRootDpadEnabled(void *container, BOOL enabled);
extern void SetWidgetRootTouchEnabled(void *container, BOOL enabled);
extern void SetFocusedWidget(void *container, void *element);
extern void SetWidgetRootInputCallback(void *container, void (*callback)(void *element));
extern void ResolveEntryStoreWord(void *container, int id, void (*callback)(void *element));
extern fx32 NextSharedRandom16Scaled(u32 range);
extern void ChangeMenuState(int state);
extern void OnPopupElementTouched(void *element);
extern void SelectMenuEntry1(void *element);
extern void SelectMenuEntry2(void *element);
extern void SelectMenuEntry3(void *element);
extern void SelectMenuEntry4(void *element);
extern void SetMenuStateFlag10(void *element);
extern void SetMenuSelection2(void *element);
extern void SetMenuSelection1(void *element);

static inline void SetElementEnabled(void *container, int elementId, BOOL enabled)
{
    SetEntrySlotsVisible(container, FindWidgetById(container, elementId), enabled);
}

static inline void SetElementMode(void *container, int elementId, int mode)
{
    SetWidgetRecordMode(container, (const struct WidgetPositionRecord *)(FindWidgetById(container, elementId)), mode);
}

static inline void SetElementNumber(void *container, int elementId, int value)
{
    SetWidgetAnimationFrame(container, (const struct WidgetPositionRecord *)(FindWidgetById(container, elementId)), value);
}

static inline void SetElementPriority(void *container, int elementId, int priority)
{
    SetIndexedRecordPriority(container, ((ObjElement *)FindWidgetById(container, elementId))->animIndex, priority);
}

static inline void GetElementPosition(void *container, int elementId, WidgetPoint *position)
{
    ResolveWidgetPositionComponents(container, FindWidgetById(container, elementId), position,
                                    WIDGET_POSITION_COMBINED_XY);
}

static inline void SetElementPosition(void *container, int elementId, WidgetPoint *position)
{
    SetWidgetPosition(container, FindWidgetById(container, elementId), position, WIDGET_POSITION_COMBINED_XY);
}

#define RESOURCE_KEY(handle, index) (((((handle) + 0x8000U) & 0xfffffc) << 7) | 0x80000000 | (index))

/*
 * Set up the ov002 menu: allocate and clear the menu context, load both screens' backgrounds and
 * object sets, hide the entry and category markers the save data has not unlocked, place the level
 * badge (80 and over, or 50 and over), reset the selection view, focus the element entryMode asks
 * for, install the element callbacks, start the cloud scroll and enter menu state 0.
 *
 * In the badge blocks the original stores the raised Y coordinate before it reloads the context
 * pointer; the two volatile accesses keep that order, as in ov015's SetupPanelGraphics.
 */
void InitMenuContext(int entryMode)
{
    BgContainerConfig mainBgConfig = gOv002MenuMainBgConfig;
    BgContainerConfig subBgConfig = gOv002MenuSubBgConfig;
    ObjManagerConfig mainObjConfig = gOv002MenuMainObjConfig;
    ObjManagerConfig subObjConfig = gOv002MenuSubObjConfig;
    BgGraphicsData bgData;
    WidgetPoint highPosition;
    WidgetPoint midPosition;
    void *archive;
    void *subArchive;
    BgEntry *entry;
    int level;
    BgRecord *record;
    int focus;

    InitOv002SubPanelGraphics();
    gOv002MenuWork = NNSi_FndAllocFromDefaultHeap(sizeof(MenuContext));
    MI_CpuFill8(gOv002MenuWork, 0, sizeof(MenuContext));
    gOv002MenuWork->state = -1;
    gOv002MenuWork->mode = 0;
    LoadPackedFileView(gOv002MenuWork->fileView, gPanelUiResourcePaths[2], TRUE);
    gOv002MenuWork->messageHandle = Msg_OpenContainerAndReadHeader(sOv002_WxcWlmP2_0206c410, 0x10, 0);
    GX_SetBankForSubOBJExtPltt(0x100);
    GX_SetBankForOBJExtPltt(0);
    *(vu32 *)0x04000000 = (*(vu32 *)0x04000000 & ~0x1f00) | 0x1f00;
    *(vu32 *)0x04001000 = (*(vu32 *)0x04001000 & ~0x1f00) | 0x1e00;
    ResetOv002PanelGraphics();

    mainObjConfig.cellResourceId = RESOURCE_KEY(gOv002MenuWork->messageHandle, 2);
    mainObjConfig.animResourceId = RESOURCE_KEY(gOv002MenuWork->messageHandle, 3);
    InitBackgroundContainer(gOv002MenuWork->mainBg, &mainBgConfig);
    LoadTagTrackerResourceFile(gOv002MenuWork->mainBg, RESOURCE_KEY(gOv002MenuWork->messageHandle, 0));
    archive = LoadFileAllocFromHeapTail(RESOURCE_KEY(gOv002MenuWork->messageHandle, 1), 0x10);
    GetBgDataFromArchive(&bgData, archive, -1, 0, 0);
    GX_LoadBGPltt(bgData.palette->data, 0, bgData.palette->size);
    GX_LoadBG0Char(bgData.character->data, 0, bgData.character->size);
    NNSi_FndFreeFromDefaultHeap(archive);
    archive = LoadFileAllocFromHeapTail(gPanelUiResourcePaths[0], 0x10);
    GetBgDataFromArchive(&bgData, archive, -1, 0, 0);
    GX_LoadBG0Char(bgData.character->data, 0x7000, bgData.character->size);
    NNSi_FndFreeFromDefaultHeap(archive);
    entry = FindActiveBackgroundScreenResourceById(gOv002MenuWork->mainBg, 0);
    GX_LoadBG1Scr(entry->screen->data, 0, entry->screen->size);
    entry = FindActiveBackgroundScreenResourceById(gOv002MenuWork->mainBg, 2);
    GX_LoadBG0Scr(entry->screen->data, FindActiveRecordById(gOv002MenuWork->mainBg, 2)->scrollY << 6,
                  entry->screen->size);

    InitializeResourceContainer(gOv002MenuWork->mainObj, NULL);
    InitObjManagerAndMark(gOv002MenuWork->mainObj, &mainObjConfig);
    CreateWidgetImageEntry(gOv002MenuWork->mainObj, gPanelUiResourcePaths[1]);
    LoadWidgetDescriptorsFromFile(gOv002MenuWork->mainObj, mainObjConfig.animResourceId, 0x14);
    SetAllElementObjectModes(gOv002MenuWork->mainObj, 3);
    SetElementMode(gOv002MenuWork->mainObj, 4, 0);
    SetElementMode(gOv002MenuWork->mainObj, 5, 0);
    SetElementMode(gOv002MenuWork->mainObj, 6, 0);
    SetElementMode(gOv002MenuWork->mainObj, 7, 0);
    SetElementMode(gOv002MenuWork->mainObj, 8, 0);
    SetElementMode(gOv002MenuWork->mainObj, 9, 0);
    SetElementMode(gOv002MenuWork->mainObj, 10, 0);
    SetElementMode(gOv002MenuWork->mainObj, 11, 0);
    SetElementMode(gOv002MenuWork->mainObj, 12, 0);
    SetElementMode(gOv002MenuWork->mainObj, 13, 0);
    SetElementMode(gOv002MenuWork->mainObj, 14, 0);
    SetElementMode(gOv002MenuWork->mainObj, 15, 0);
    SetElementMode(gOv002MenuWork->mainObj, 16, 0);
    SetElementMode(gOv002MenuWork->mainObj, 17, 0);
    SetElementMode(gOv002MenuWork->mainObj, 18, 0);
    SetElementNumber(gOv002MenuWork->mainObj, 15, 0);
    SetElementNumber(gOv002MenuWork->mainObj, 16, 2);
    SetElementNumber(gOv002MenuWork->mainObj, 17, 4);
    SetElementNumber(gOv002MenuWork->mainObj, 18, 5);
    SetElementPriority(gOv002MenuWork->mainObj, 6, 0xff);
    SetElementPriority(gOv002MenuWork->mainObj, 7, 0xff);
    SetElementPriority(gOv002MenuWork->mainObj, 8, 0xff);
    SetElementPriority(gOv002MenuWork->mainObj, 9, 0xff);
    SetElementPriority(gOv002MenuWork->mainObj, 10, 0xff);
    SetElementPriority(gOv002MenuWork->mainObj, 11, 0xff);
    SetElementPriority(gOv002MenuWork->mainObj, 12, 0xff);
    SetElementPriority(gOv002MenuWork->mainObj, 13, 0xff);
    SetElementPriority(gOv002MenuWork->mainObj, 4, 0);
    SetElementPriority(gOv002MenuWork->mainObj, 5, 0);

    subObjConfig.cellResourceId = RESOURCE_KEY(gOv002MenuWork->messageHandle, 6);
    subObjConfig.animResourceId = RESOURCE_KEY(gOv002MenuWork->messageHandle, 7);
    InitBackgroundContainer(gOv002MenuWork->subBg, &subBgConfig);
    LoadTagTrackerResourceFile(gOv002MenuWork->subBg, RESOURCE_KEY(gOv002MenuWork->messageHandle, 4));
    subArchive = LoadFileAllocFromHeapTail(RESOURCE_KEY(gOv002MenuWork->messageHandle, 5), 0x10);
    GetBgDataFromArchive(&bgData, subArchive, -1, 0, 0);
    GXS_LoadBGPltt(bgData.palette->data, 0, bgData.palette->size);
    GXS_LoadBG0Char(bgData.character->data, 0, bgData.character->size);
    entry = FindActiveBackgroundScreenResourceById(gOv002MenuWork->subBg, 0);
    GXS_LoadBG1Scr(entry->screen->data, 0, entry->screen->size);
    entry = FindActiveBackgroundScreenResourceById(gOv002MenuWork->subBg, 2);
    record = FindActiveRecordById(gOv002MenuWork->subBg, 2);
    GXS_LoadBG0Scr(entry->screen->data, record->scrollY << 6, entry->screen->size);

    InitializeResourceContainer(gOv002MenuWork->subObj, NULL);
    InitObjManagerAndMark(gOv002MenuWork->subObj, &subObjConfig);
    CreateWidgetImageEntry(gOv002MenuWork->subObj, gPanelUiResourcePaths[3]);
    LoadWidgetDescriptorsFromFile(gOv002MenuWork->subObj, subObjConfig.animResourceId, 0xd);
    SetAllElementObjectModes(gOv002MenuWork->subObj, 3);
    SetWidgetRecordMode(gOv002MenuWork->subObj, (const struct WidgetPositionRecord *)(FindWidgetById(gOv002MenuWork->subObj, 11)), 1);
    SetWidgetRecordMode(gOv002MenuWork->subObj, (const struct WidgetPositionRecord *)(FindWidgetById(gOv002MenuWork->subObj, 12)), 1);
    SetWidgetRecordMode(gOv002MenuWork->subObj, (const struct WidgetPositionRecord *)(FindWidgetById(gOv002MenuWork->subObj, 0)), 1);
    SetElementEnabled(gOv002MenuWork->subObj, 5, TRUE);
    SetElementMode(gOv002MenuWork->subObj, 5, 0);
    ClearWidgetRecordActiveBits(gOv002MenuWork->subObj, (const struct WidgetPositionRecord *)(FindWidgetById(gOv002MenuWork->subObj, 0x15)));
    ClearWidgetRecordActiveBits(gOv002MenuWork->subObj, (const struct WidgetPositionRecord *)(FindWidgetById(gOv002MenuWork->subObj, 0x16)));
    if (HasAnyMenuEntryUnlocked()) {
        gOv002MenuWork->flags.hasUnlockedEntry = TRUE;
    } else {
        SetEntrySlotsVisible(gOv002MenuWork->subObj, FindWidgetById(gOv002MenuWork->subObj, 0x16), FALSE);
    }
    if (GetCategoryFlagState(GetRecordFlagBits(), -1)) {
        gOv002MenuWork->flags.hasCategory = TRUE;
    } else {
        SetEntrySlotsVisible(gOv002MenuWork->subObj, FindWidgetById(gOv002MenuWork->subObj, 0x15), FALSE);
    }
    if (!DispatchContextCommand(1, 0, 0, 0)) {
        gOv002MenuWork->flags.hasProgress = TRUE;
        ApplySelectedSubitemValues(gOv002MenuWork->subObj, FindWidgetById(gOv002MenuWork->subObj, 2), 0);
    }

    level = DispatchContextCommand(8, 0, 0, 0);
    if (DispatchContextCommand(5, 0, 0, 0)) {
        level = 0;
    }
    if (level >= 80) {
        SetEntrySlotsVisible(gOv002MenuWork->subObj, FindWidgetById(gOv002MenuWork->subObj, 0x18), TRUE);
        GetElementPosition(gOv002MenuWork->subObj, 0x18, &highPosition);
        *(volatile fx32 *)&highPosition.y = ((highPosition.y >> 12) + 20) << 12;
        SetElementPosition((*(MenuContext *volatile *)&gOv002MenuWork)->subObj, 0x18, &highPosition);
    } else if (level >= 50) {
        SetEntrySlotsVisible(gOv002MenuWork->subObj, FindWidgetById(gOv002MenuWork->subObj, 0x17), TRUE);
        GetElementPosition(gOv002MenuWork->subObj, 0x17, &midPosition);
        *(volatile fx32 *)&midPosition.y = ((midPosition.y >> 12) + 20) << 12;
        SetElementPosition((*(MenuContext *volatile *)&gOv002MenuWork)->subObj, 0x17, &midPosition);
    }

    LoadAvatarObjPalette(TRUE);
    {
        MenuContext *context = gOv002MenuWork;

        context->profileCopy = *GetPackedFields();
        context->selection.selection = &context->profileCopy;
    }
    ResetSelectionView(&gOv002MenuWork->selection);
    gOv002MenuWork->selection.basePriority = 200;
    gOv002MenuWork->selection.flags.mode = 3;
    gOv002MenuWork->selection.position.x = 200 << 12;
    gOv002MenuWork->selection.position.y = 67 << 12;
    BuildSelectionViewRecords(gOv002MenuWork->subObj, &gOv002MenuWork->selection);
    SetGroupSlotsVisible(gOv002MenuWork->subObj, &gOv002MenuWork->selection, TRUE);
    SetWidgetRootDpadEnabled(gOv002MenuWork->subObj, TRUE);
    SetWidgetRootTouchEnabled(gOv002MenuWork->subObj, TRUE);
    gOv002MenuWork->selectedIndex = 0;
    focus = 1;
    switch (entryMode) {
    case 0:
    case 2:
        if (gOv002MenuWork->flags.hasCategory) {
            SetWidgetAnimationFrame(gOv002MenuWork->subObj, (const struct WidgetPositionRecord *)(FindWidgetById(gOv002MenuWork->subObj, 0x15)), 1);
        }
        break;
    case 3:
        if (DispatchContextCommand(1, 0, 0, 0)) {
            gOv002MenuWork->selectedIndex = 1;
            focus = 2;
            if (gOv002MenuWork->flags.hasUnlockedEntry) {
                SetWidgetAnimationFrame(gOv002MenuWork->subObj, (const struct WidgetPositionRecord *)(FindWidgetById(gOv002MenuWork->subObj, 0x16)),
                                    1);
            }
        } else if (gOv002MenuWork->flags.hasCategory) {
            SetWidgetAnimationFrame(gOv002MenuWork->subObj, (const struct WidgetPositionRecord *)(FindWidgetById(gOv002MenuWork->subObj, 0x15)), 1);
        }
        break;
    case 6:
        gOv002MenuWork->selectedIndex = 3;
        focus = 4;
        break;
    }
    SetFocusedWidget(gOv002MenuWork->subObj, FindWidgetById(gOv002MenuWork->subObj, focus));
    SetWidgetRootInputCallback(gOv002MenuWork->subObj, OnPopupElementTouched);
    ResolveEntryStoreWord(gOv002MenuWork->subObj, 1, SelectMenuEntry1);
    ResolveEntryStoreWord(gOv002MenuWork->subObj, 2, SelectMenuEntry2);
    ResolveEntryStoreWord(gOv002MenuWork->subObj, 3, SelectMenuEntry3);
    ResolveEntryStoreWord(gOv002MenuWork->subObj, 4, SelectMenuEntry4);
    ResolveEntryStoreWord(gOv002MenuWork->subObj, 5, SetMenuStateFlag10);
    ResolveEntryStoreWord(gOv002MenuWork->subObj, 11, SetMenuSelection2);
    ResolveEntryStoreWord(gOv002MenuWork->subObj, 12, SetMenuSelection1);
    gOv002MenuWork->cloudSpeedX = NextSharedRandom16Scaled(0x1000) + 0x1000;
    gOv002MenuWork->cloudOffsetX = NextSharedRandom16Scaled(0);
    gOv002MenuWork->cloudSpeedY = NextSharedRandom16Scaled(0x1000) + 0x1000;
    gOv002MenuWork->cloudOffsetY = (NextSharedRandom16Scaled(0) + 0x80) << 12;
    NNSi_FndFreeFromDefaultHeap(subArchive);
    ChangeMenuState(0);
}
