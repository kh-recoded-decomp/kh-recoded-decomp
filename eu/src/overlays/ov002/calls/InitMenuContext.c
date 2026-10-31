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

extern MenuContext *data_ov002_0206c464;
extern const BgContainerConfig data_ov002_0206acc4;
extern const BgContainerConfig data_ov002_0206acd8;
extern const ObjManagerConfig data_ov002_0206acec;
extern const ObjManagerConfig data_ov002_0206ad04;
extern u32 gPanelUiResourcePaths[4];
extern const char sOv002_WxcWlmP2_0206c410[];

extern void func_ov002_02062368(void);
extern void *NNSi_FndAllocFromDefaultHeap(u32 size);
extern void MI_CpuFill8(void *dst, u8 value, u32 size);
extern void LoadPackedFileView(void *view, u32 path, BOOL fromTop);
extern int Msg_OpenContainerAndReadHeader(const char *path, u32 kind, u32 fromTop);
extern void GX_SetBankForSubOBJExtPltt(int bank);
extern void GX_SetBankForOBJExtPltt(int bank);
extern void func_ov002_020629a8(void);
extern void InitBackgroundContainer(void *container, const BgContainerConfig *config);
extern void func_ov027_020b7e44(void *container, u32 resourceId);
extern void *func_0202c4a0(u32 resourceId, u32 kind);
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
extern BgEntry *func_ov027_020b8578(void *container, int entryId);
extern BgRecord *FindActiveRecordById(void *container, int id);
extern void InitializeResourceContainer(void *container, ObjManagerConfig *config);
extern void InitObjManagerAndMark(void *container, ObjManagerConfig *config);
extern void func_ov027_020b9098(void *container, u32 value);
extern void func_ov027_020b8fb8(void *container, u32 resourceId, int count);
extern void SetAllElementObjectModes(void *container, int mode);
extern void *FindWidgetById(void *container, int id);
extern void func_ov027_020b97d8(void *container, void *element, int mode);
extern void func_ov027_020b96c0(void *container, void *element, int layer);
extern void SetIndexedRecordPriority(void *container, int animIndex, int value);
extern void SetEntrySlotsVisible(void *container, void *element, BOOL visible);
extern void func_ov027_020b9604(void *container, void *element);
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
extern void func_ov027_020b90b8(void *container, void (*callback)(void *element));
extern void ResolveEntryStoreWord(void *container, int id, void (*callback)(void *element));
extern fx32 func_0202a9e4(u32 range);
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
    func_ov027_020b97d8(container, FindWidgetById(container, elementId), mode);
}

static inline void SetElementNumber(void *container, int elementId, int value)
{
    func_ov027_020b96c0(container, FindWidgetById(container, elementId), value);
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
    func_ov027_020b91e8(container, FindWidgetById(container, elementId), position, WIDGET_POSITION_COMBINED_XY);
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
    BgContainerConfig mainBgConfig = data_ov002_0206acc4;
    BgContainerConfig subBgConfig = data_ov002_0206acd8;
    ObjManagerConfig mainObjConfig = data_ov002_0206acec;
    ObjManagerConfig subObjConfig = data_ov002_0206ad04;
    BgGraphicsData bgData;
    WidgetPoint highPosition;
    WidgetPoint midPosition;
    void *archive;
    void *subArchive;
    BgEntry *entry;
    int level;
    BgRecord *record;
    int focus;

    func_ov002_02062368();
    data_ov002_0206c464 = NNSi_FndAllocFromDefaultHeap(sizeof(MenuContext));
    MI_CpuFill8(data_ov002_0206c464, 0, sizeof(MenuContext));
    data_ov002_0206c464->state = -1;
    data_ov002_0206c464->mode = 0;
    LoadPackedFileView(data_ov002_0206c464->fileView, gPanelUiResourcePaths[2], TRUE);
    data_ov002_0206c464->messageHandle = Msg_OpenContainerAndReadHeader(sOv002_WxcWlmP2_0206c410, 0x10, 0);
    GX_SetBankForSubOBJExtPltt(0x100);
    GX_SetBankForOBJExtPltt(0);
    *(vu32 *)0x04000000 = (*(vu32 *)0x04000000 & ~0x1f00) | 0x1f00;
    *(vu32 *)0x04001000 = (*(vu32 *)0x04001000 & ~0x1f00) | 0x1e00;
    func_ov002_020629a8();

    mainObjConfig.cellResourceId = RESOURCE_KEY(data_ov002_0206c464->messageHandle, 2);
    mainObjConfig.animResourceId = RESOURCE_KEY(data_ov002_0206c464->messageHandle, 3);
    InitBackgroundContainer(data_ov002_0206c464->mainBg, &mainBgConfig);
    func_ov027_020b7e44(data_ov002_0206c464->mainBg, RESOURCE_KEY(data_ov002_0206c464->messageHandle, 0));
    archive = func_0202c4a0(RESOURCE_KEY(data_ov002_0206c464->messageHandle, 1), 0x10);
    GetBgDataFromArchive(&bgData, archive, -1, 0, 0);
    GX_LoadBGPltt(bgData.palette->data, 0, bgData.palette->size);
    GX_LoadBG0Char(bgData.character->data, 0, bgData.character->size);
    NNSi_FndFreeFromDefaultHeap(archive);
    archive = func_0202c4a0(gPanelUiResourcePaths[0], 0x10);
    GetBgDataFromArchive(&bgData, archive, -1, 0, 0);
    GX_LoadBG0Char(bgData.character->data, 0x7000, bgData.character->size);
    NNSi_FndFreeFromDefaultHeap(archive);
    entry = func_ov027_020b8578(data_ov002_0206c464->mainBg, 0);
    GX_LoadBG1Scr(entry->screen->data, 0, entry->screen->size);
    entry = func_ov027_020b8578(data_ov002_0206c464->mainBg, 2);
    GX_LoadBG0Scr(entry->screen->data, FindActiveRecordById(data_ov002_0206c464->mainBg, 2)->scrollY << 6,
                  entry->screen->size);

    InitializeResourceContainer(data_ov002_0206c464->mainObj, NULL);
    InitObjManagerAndMark(data_ov002_0206c464->mainObj, &mainObjConfig);
    func_ov027_020b9098(data_ov002_0206c464->mainObj, gPanelUiResourcePaths[1]);
    func_ov027_020b8fb8(data_ov002_0206c464->mainObj, mainObjConfig.animResourceId, 0x14);
    SetAllElementObjectModes(data_ov002_0206c464->mainObj, 3);
    SetElementMode(data_ov002_0206c464->mainObj, 4, 0);
    SetElementMode(data_ov002_0206c464->mainObj, 5, 0);
    SetElementMode(data_ov002_0206c464->mainObj, 6, 0);
    SetElementMode(data_ov002_0206c464->mainObj, 7, 0);
    SetElementMode(data_ov002_0206c464->mainObj, 8, 0);
    SetElementMode(data_ov002_0206c464->mainObj, 9, 0);
    SetElementMode(data_ov002_0206c464->mainObj, 10, 0);
    SetElementMode(data_ov002_0206c464->mainObj, 11, 0);
    SetElementMode(data_ov002_0206c464->mainObj, 12, 0);
    SetElementMode(data_ov002_0206c464->mainObj, 13, 0);
    SetElementMode(data_ov002_0206c464->mainObj, 14, 0);
    SetElementMode(data_ov002_0206c464->mainObj, 15, 0);
    SetElementMode(data_ov002_0206c464->mainObj, 16, 0);
    SetElementMode(data_ov002_0206c464->mainObj, 17, 0);
    SetElementMode(data_ov002_0206c464->mainObj, 18, 0);
    SetElementNumber(data_ov002_0206c464->mainObj, 15, 0);
    SetElementNumber(data_ov002_0206c464->mainObj, 16, 2);
    SetElementNumber(data_ov002_0206c464->mainObj, 17, 4);
    SetElementNumber(data_ov002_0206c464->mainObj, 18, 5);
    SetElementPriority(data_ov002_0206c464->mainObj, 6, 0xff);
    SetElementPriority(data_ov002_0206c464->mainObj, 7, 0xff);
    SetElementPriority(data_ov002_0206c464->mainObj, 8, 0xff);
    SetElementPriority(data_ov002_0206c464->mainObj, 9, 0xff);
    SetElementPriority(data_ov002_0206c464->mainObj, 10, 0xff);
    SetElementPriority(data_ov002_0206c464->mainObj, 11, 0xff);
    SetElementPriority(data_ov002_0206c464->mainObj, 12, 0xff);
    SetElementPriority(data_ov002_0206c464->mainObj, 13, 0xff);
    SetElementPriority(data_ov002_0206c464->mainObj, 4, 0);
    SetElementPriority(data_ov002_0206c464->mainObj, 5, 0);

    subObjConfig.cellResourceId = RESOURCE_KEY(data_ov002_0206c464->messageHandle, 6);
    subObjConfig.animResourceId = RESOURCE_KEY(data_ov002_0206c464->messageHandle, 7);
    InitBackgroundContainer(data_ov002_0206c464->subBg, &subBgConfig);
    func_ov027_020b7e44(data_ov002_0206c464->subBg, RESOURCE_KEY(data_ov002_0206c464->messageHandle, 4));
    subArchive = func_0202c4a0(RESOURCE_KEY(data_ov002_0206c464->messageHandle, 5), 0x10);
    GetBgDataFromArchive(&bgData, subArchive, -1, 0, 0);
    GXS_LoadBGPltt(bgData.palette->data, 0, bgData.palette->size);
    GXS_LoadBG0Char(bgData.character->data, 0, bgData.character->size);
    entry = func_ov027_020b8578(data_ov002_0206c464->subBg, 0);
    GXS_LoadBG1Scr(entry->screen->data, 0, entry->screen->size);
    entry = func_ov027_020b8578(data_ov002_0206c464->subBg, 2);
    record = FindActiveRecordById(data_ov002_0206c464->subBg, 2);
    GXS_LoadBG0Scr(entry->screen->data, record->scrollY << 6, entry->screen->size);

    InitializeResourceContainer(data_ov002_0206c464->subObj, NULL);
    InitObjManagerAndMark(data_ov002_0206c464->subObj, &subObjConfig);
    func_ov027_020b9098(data_ov002_0206c464->subObj, gPanelUiResourcePaths[3]);
    func_ov027_020b8fb8(data_ov002_0206c464->subObj, subObjConfig.animResourceId, 0xd);
    SetAllElementObjectModes(data_ov002_0206c464->subObj, 3);
    func_ov027_020b97d8(data_ov002_0206c464->subObj, FindWidgetById(data_ov002_0206c464->subObj, 11), 1);
    func_ov027_020b97d8(data_ov002_0206c464->subObj, FindWidgetById(data_ov002_0206c464->subObj, 12), 1);
    func_ov027_020b97d8(data_ov002_0206c464->subObj, FindWidgetById(data_ov002_0206c464->subObj, 0), 1);
    SetElementEnabled(data_ov002_0206c464->subObj, 5, TRUE);
    SetElementMode(data_ov002_0206c464->subObj, 5, 0);
    func_ov027_020b9604(data_ov002_0206c464->subObj, FindWidgetById(data_ov002_0206c464->subObj, 0x15));
    func_ov027_020b9604(data_ov002_0206c464->subObj, FindWidgetById(data_ov002_0206c464->subObj, 0x16));
    if (HasAnyMenuEntryUnlocked()) {
        data_ov002_0206c464->flags.hasUnlockedEntry = TRUE;
    } else {
        SetEntrySlotsVisible(data_ov002_0206c464->subObj, FindWidgetById(data_ov002_0206c464->subObj, 0x16), FALSE);
    }
    if (GetCategoryFlagState(GetRecordFlagBits(), -1)) {
        data_ov002_0206c464->flags.hasCategory = TRUE;
    } else {
        SetEntrySlotsVisible(data_ov002_0206c464->subObj, FindWidgetById(data_ov002_0206c464->subObj, 0x15), FALSE);
    }
    if (!DispatchContextCommand(1, 0, 0, 0)) {
        data_ov002_0206c464->flags.hasProgress = TRUE;
        ApplySelectedSubitemValues(data_ov002_0206c464->subObj, FindWidgetById(data_ov002_0206c464->subObj, 2), 0);
    }

    level = DispatchContextCommand(8, 0, 0, 0);
    if (DispatchContextCommand(5, 0, 0, 0)) {
        level = 0;
    }
    if (level >= 80) {
        SetEntrySlotsVisible(data_ov002_0206c464->subObj, FindWidgetById(data_ov002_0206c464->subObj, 0x18), TRUE);
        GetElementPosition(data_ov002_0206c464->subObj, 0x18, &highPosition);
        *(volatile fx32 *)&highPosition.y = ((highPosition.y >> 12) + 20) << 12;
        SetElementPosition((*(MenuContext *volatile *)&data_ov002_0206c464)->subObj, 0x18, &highPosition);
    } else if (level >= 50) {
        SetEntrySlotsVisible(data_ov002_0206c464->subObj, FindWidgetById(data_ov002_0206c464->subObj, 0x17), TRUE);
        GetElementPosition(data_ov002_0206c464->subObj, 0x17, &midPosition);
        *(volatile fx32 *)&midPosition.y = ((midPosition.y >> 12) + 20) << 12;
        SetElementPosition((*(MenuContext *volatile *)&data_ov002_0206c464)->subObj, 0x17, &midPosition);
    }

    LoadAvatarObjPalette(TRUE);
    {
        MenuContext *context = data_ov002_0206c464;

        context->profileCopy = *GetPackedFields();
        context->selection.selection = &context->profileCopy;
    }
    ResetSelectionView(&data_ov002_0206c464->selection);
    data_ov002_0206c464->selection.basePriority = 200;
    data_ov002_0206c464->selection.flags.mode = 3;
    data_ov002_0206c464->selection.position.x = 200 << 12;
    data_ov002_0206c464->selection.position.y = 67 << 12;
    BuildSelectionViewRecords(data_ov002_0206c464->subObj, &data_ov002_0206c464->selection);
    SetGroupSlotsVisible(data_ov002_0206c464->subObj, &data_ov002_0206c464->selection, TRUE);
    SetWidgetRootDpadEnabled(data_ov002_0206c464->subObj, TRUE);
    SetWidgetRootTouchEnabled(data_ov002_0206c464->subObj, TRUE);
    data_ov002_0206c464->selectedIndex = 0;
    focus = 1;
    switch (entryMode) {
    case 0:
    case 2:
        if (data_ov002_0206c464->flags.hasCategory) {
            func_ov027_020b96c0(data_ov002_0206c464->subObj, FindWidgetById(data_ov002_0206c464->subObj, 0x15), 1);
        }
        break;
    case 3:
        if (DispatchContextCommand(1, 0, 0, 0)) {
            data_ov002_0206c464->selectedIndex = 1;
            focus = 2;
            if (data_ov002_0206c464->flags.hasUnlockedEntry) {
                func_ov027_020b96c0(data_ov002_0206c464->subObj, FindWidgetById(data_ov002_0206c464->subObj, 0x16),
                                    1);
            }
        } else if (data_ov002_0206c464->flags.hasCategory) {
            func_ov027_020b96c0(data_ov002_0206c464->subObj, FindWidgetById(data_ov002_0206c464->subObj, 0x15), 1);
        }
        break;
    case 6:
        data_ov002_0206c464->selectedIndex = 3;
        focus = 4;
        break;
    }
    SetFocusedWidget(data_ov002_0206c464->subObj, FindWidgetById(data_ov002_0206c464->subObj, focus));
    func_ov027_020b90b8(data_ov002_0206c464->subObj, OnPopupElementTouched);
    ResolveEntryStoreWord(data_ov002_0206c464->subObj, 1, SelectMenuEntry1);
    ResolveEntryStoreWord(data_ov002_0206c464->subObj, 2, SelectMenuEntry2);
    ResolveEntryStoreWord(data_ov002_0206c464->subObj, 3, SelectMenuEntry3);
    ResolveEntryStoreWord(data_ov002_0206c464->subObj, 4, SelectMenuEntry4);
    ResolveEntryStoreWord(data_ov002_0206c464->subObj, 5, SetMenuStateFlag10);
    ResolveEntryStoreWord(data_ov002_0206c464->subObj, 11, SetMenuSelection2);
    ResolveEntryStoreWord(data_ov002_0206c464->subObj, 12, SetMenuSelection1);
    data_ov002_0206c464->cloudSpeedX = func_0202a9e4(0x1000) + 0x1000;
    data_ov002_0206c464->cloudOffsetX = func_0202a9e4(0);
    data_ov002_0206c464->cloudSpeedY = func_0202a9e4(0x1000) + 0x1000;
    data_ov002_0206c464->cloudOffsetY = (func_0202a9e4(0) + 0x80) << 12;
    NNSi_FndFreeFromDefaultHeap(subArchive);
    ChangeMenuState(0);
}
