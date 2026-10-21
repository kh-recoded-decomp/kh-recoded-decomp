#pragma opt_lifetimes off
#pragma opt_common_subs off
#pragma opt_propagation off
#pragma opt_rotateloops off
#include "nitro/types.h"

typedef struct StringTable {
    void *buffer;
    u32 count;
    u8 *entries;
} StringTable;

typedef struct TextWindow {
    u8 data[0x34];
} TextWindow;

typedef struct WindowStyle {
    u16 unk_00[4];
    u16 fillColor;
    u16 unk_0A[3];
} WindowStyle;

typedef struct ObjManagerConfig {
    int resource;
    int unk_04;
    int unk_08;
    int unk_0C;
} ObjManagerConfig;

typedef struct WeaponParams {
    u32 kind;
    int unk_04;
    int unk_08;
    void *attachSlot;
    int scale;
    int unk_14;
} WeaponParams;

typedef struct MenuEntry {
    u16 *label;
    u16 *description;
    int id;
} MenuEntry;

typedef struct ElementPair {
    int icon;
    int text;
} ElementPair;

typedef struct ResMdl {
    u8 pad_00[0x40];
    u8 nodeDict[1];
} ResMdl;

typedef struct RenderObj {
    u32 flag;
    ResMdl *resMdl;
    u8 pad_08[0x24];
    void *userData;
} RenderObj;

typedef struct CharacterModel {
    u8 pad_00[0x20];
    RenderObj renderObj;
    u8 pad_50[0xa8 - 0x50];
    int positionY;
    u8 pad_ac[0xd8 - 0xac];
    u8 blendTable[0x2c];
} CharacterModel;

typedef struct AttachSlot {
    u8 data[0x30];
} AttachSlot;

typedef struct RootMenu {
    u8 cursor;
    u8 entryCount;
    u8 state;
    u8 mode;
    u8 pad_04[4];
    BOOL isFullMenu;
    BOOL isWeaponLocked;
    u8 pad_10[2];
    u16 unlockMessage;
    int textureKeyA;
    int textureKeyB;
    CharacterModel model;
    u8 weapon[8];
    u8 weaponModel[0x228];
    u8 animA[0x24];
    u8 animB[0x24];
    int jointIndexA;
    int jointIndexB;
    AttachSlot attachSlots[2];
    u32 projection[14];
    TextWindow windows[4];
    MenuEntry entries[8];
    u16 *extraLabels[4];
    int layoutContext;
    void *objManager;
    ElementPair itemElements[8];
    int cursorElement;
    int headerElement;
    int frameElement;
    int arrowsLeft[2];
    int arrowsRight[2];
    StringTable strings;
} RootMenu;

typedef struct SaveData {
    u8 pad_0000[0x28d4];
    s8 storyProgress;
    s8 areaId;
} SaveData;

typedef struct GameState {
    u8 pad_000[0x214];
    u32 unk_214_0 : 13;
    u32 bgmLocked : 1;
    u32 unk_214_14 : 18;
    u8 pad_218[0x27fc - 0x218];
    s8 bgmOverride;
} GameState;

extern SaveData *data_0205fe0c;
extern GameState *data_ov001_020a0460;
extern const WindowStyle data_ov074_020c5950;
extern const ObjManagerConfig data_ov074_020c5940;
extern const char data_ov074_020c59c4[];
extern const char data_ov074_020c59cc[];
extern const char data_ov074_020c59d4[];
extern const char data_ov074_020c59ec[];
extern const char data_ov074_020c59fc[];
extern const char data_ov074_020c5a08[];
extern const char data_ov074_020c5a18[];
extern const u8 data_ov074_020c5930[];
extern const u8 data_ov074_020c5920[];

extern void func_ov074_020c50b0(void *renderState);
extern void func_ov039_020be6a0(void);
extern int func_ov039_020bcb00(void);
extern int func_ov039_020bc810(void);
extern BOOL IsGlobalPackedBitSet_02027304(int bitIndex);
extern void SetGlobalPackedBit_02027320(int bitIndex);
extern int func_ov001_02064ac0(void);
extern void func_ov039_020be5b8(int position, int size, int palette, TextWindow *window, WindowStyle *style);
extern int OS_SNPrintf_02002468(char *dst, u32 len, const char *fmt, ...);
extern void func_ov027_020ba25c(StringTable *table, const char *path, int flags);
extern u16 *func_ov027_020ba2a8(StringTable *table, int index);
extern u16 *func_ov039_020bcb20(SaveData *save);
extern void func_ov039_020bcd04(TextWindow *window, int messageId, u16 *text);
extern void DrawTextAnchored_020015a0(TextWindow *window, int x, int y, int color, u32 flags, const u16 *text);
extern void SetSelectionIfChanged_020bc92c(int id);
extern u8 func_ov039_020bc828(void);
extern int func_ov039_020bc18c(void);
extern void *func_ov039_020bc1bc(void);
extern int func_ov039_020bc220(int group, int index);
extern void InitObjManagerAndMark_020b9060(void *manager, ObjManagerConfig *config);
extern void func_ov027_020b8f98(void *manager, int resource, int count);
extern void func_ov027_020b7e24(int context, int resource);
extern int func_ov027_020b90a4(void *manager, int elementId);
extern void func_ov027_020b97b8(void *manager, int element, int mode);
extern void func_ov027_020b9580(void *manager, int element, BOOL visible);
extern void func_ov039_020bc318(int a, int b, int c, int d, int e, u16 f);
extern int func_ov039_020bc914(void);
extern void func_ov039_020bc414(int a, int b, int c);
extern void SetSecondaryElementEnabled_020bc084(BOOL enabled);
extern void func_ov039_020bc03c(int value);
extern BOOL func_ov001_020645c8(u32 itemId);
extern void *func_0202c48c(const char *path, int heap);
extern int Msg_OpenContainerAndReadHeader_0202cc6c(const char *name, u32 mode, BOOL allocFromEnd);
extern void func_0202ed3c(void *model, const char *path, void *file, int heap);
extern BOOL func_0202e9ec(void *anim, void *model, u32 key, int heap);
extern void NNSi_FndFreeFromDefaultHeap_0202a1c4(void *block);
extern void func_ov021_020a9524(void);
extern void func_ov021_020a9598(int value);
extern void func_ov021_020a98e8(void *weapon, int value);
extern u8 *GetOverlaySelectionRecord(u32 selectionIndex);
extern void func_ov021_020a998c(void *weapon, WeaponParams *params);
extern void func_ov021_020a95b4(void);
extern int FindResourceIndexByName_0201aafc(const void *dict, const void *name);
extern void ClearSbcCallback_020188b8(RenderObj *renderObj);
extern void RegisterSbcCallback_020188a4(RenderObj *renderObj, void (*func)(void *), u8 *addr, u8 cmd, int timing);
extern void func_02006d3c(int value);
extern void LoadDefaultProjectionValues_0202a7b4(u32 *projection);
extern void selectJointAnimationBlend_0202f2cc(void *animationState, u16 trackIndex, void *blendTable, s16 blendIndex);
extern void func_0202f4e8(void *model);
extern void SetBit1WhenBit0Set_020a9ce8(void *flags, int enable);
extern void func_ov021_020a9d28(void *weapon, int value);
extern int func_ov001_02068094(int areaId);
extern void func_0204d8b8(int bgm, int fade);
extern void func_0204d7f4(int value);

static inline BOOL IsShortMenu(void)
{
    BOOL result = FALSE;
    if (func_ov039_020bcb00() && !func_ov039_020bc810()) {
        result = TRUE;
    }
    return result;
}

static inline BOOL HasEitherItem(u32 first, u32 second)
{
    BOOL result = TRUE;
    if (func_ov001_020645c8(first) == FALSE && func_ov001_020645c8(second) == FALSE) {
        result = FALSE;
    }
    return result;
}

static inline BOOL HasAnyKeyblade(void)
{
    BOOL result = TRUE;
    if (!HasEitherItem(0x3520, 0x360b) && !HasEitherItem(0x3609, 0x360a)) {
        result = FALSE;
    }
    return result;
}

static inline int FindNode(RootMenu *menu, const void *name)
{
    ResMdl *resMdl = menu->model.renderObj.resMdl;
    void *dict = resMdl ? resMdl->nodeDict : NULL;
    if (dict == NULL) {
        return -1;
    }
    return FindResourceIndexByName_0201aafc(dict, name);
}

static inline BOOL IsFlagSet(int bit)
{
    BOOL set = IsGlobalPackedBitSet_02027304(bit);
    BOOL result = TRUE;
    if (!set) {
        result = FALSE;
    }
    return result;
}

static inline BOOL HasBgmOverride(void)
{
    return data_ov001_020a0460->bgmOverride != -1;
}

static inline void AddMenuEntry(RootMenu *menu, MenuEntry *entry, int textIndex, int id)
{
    entry->label = func_ov027_020ba2a8(&menu->strings, textIndex);
    entry->description = func_ov027_020ba2a8(&menu->strings, textIndex + 1);
    entry->id = id;
}

int InitRootMenu_020c4260(RootMenu *menu)
{
    char path[64];
    WindowStyle style;
    ObjManagerConfig config;
    WeaponParams params;
    const char *menuName;
    MenuEntry *first;
    MenuEntry *entry;
    int layoutContext;
    int i;
    BOOL isResuming;
    BOOL isShort;
    int resource;
    ElementPair *pair;
    void *objManager;
    int elementId;
    int arrow;
    u16 unlockMessage;

    func_ov039_020be6a0();
    *(vu16 *)0x04000304 |= 0x8000;
    *(vu16 *)0x04000008 = (u16)((*(vu16 *)0x04000008 & ~3) | 1);
    *(vu16 *)0x0400000a = (u16)(*(vu16 *)0x0400000a & ~3);
    *(vu16 *)0x0400000c = (u16)((*(vu16 *)0x0400000c & ~3) | 2);
    *(vu16 *)0x0400000e = (u16)((*(vu16 *)0x0400000e & ~3) | 3);
    {
        int control = *(vu16 *)0x0400000c & 0x43;
        control |= 0x1e00;
        control |= 8;
        *(vu16 *)0x0400000c = (u16)control;
    }
    *(vu32 *)0x04000000 = (*(vu32 *)0x04000000 & ~0x1f00) | 0x1f00;

    menu->isFullMenu = !IsShortMenu();
    if (!menu->isFullMenu) {
        if (!IsGlobalPackedBitSet_02027304(0xf95) && data_0205fe0c->storyProgress >= 1) {
            SetGlobalPackedBit_02027320(0xf95);
            unlockMessage = 0xd;
        } else {
            if (!func_ov001_02064ac0() || IsGlobalPackedBitSet_02027304(0xfc3)) {
                goto setupWindows;
            }
            SetGlobalPackedBit_02027320(0xfc3);
            unlockMessage = 0xc;
        }
        menu->mode = 2;
        menu->unlockMessage = unlockMessage;
    }
setupWindows:
    style = data_ov074_020c5950;
    func_ov039_020be5b8(0x8, 0x20018, 2, &menu->windows[0], &style);
    func_ov039_020be5b8(0x30002, 0x10001c, 2, &menu->windows[1], &style);
    func_ov039_020be5b8(0x150000, 0x30020, 2, &menu->windows[2], &style);
    style.fillColor = 0x3a;
    func_ov039_020be5b8(0x80003, 0x7001a, 1, &menu->windows[3], &style);

    menuName = data_ov074_020c59c4;
    if (func_ov039_020bcb00() && !func_ov039_020bc810()) {
        menuName = data_ov074_020c59cc;
    }
    OS_SNPrintf_02002468(path, sizeof(path), data_ov074_020c59d4, menuName);
    func_ov027_020ba25c(&menu->strings, path, 0);

    if (func_ov039_020bcb00()) {
        menu->extraLabels[0] = func_ov027_020ba2a8(&menu->strings, 8);
        menu->extraLabels[1] = func_ov027_020ba2a8(&menu->strings, 9);
        menu->extraLabels[2] = func_ov027_020ba2a8(&menu->strings, 10);
        menu->extraLabels[3] = func_ov027_020ba2a8(&menu->strings, 11);
    }

    {
        int messageId = IsShortMenu() ? 0xa4 : 0xac;
        u16 *title = func_ov039_020bcb20(data_0205fe0c);
        func_ov039_020bcd04(&menu->windows[0], messageId, title);
        DrawTextAnchored_020015a0(&menu->windows[0], 0xbe, 2, 2, 0x20, title);
    }
    menu->state = 1;

    isShort = IsShortMenu();
    first = menu->entries;
    entry = first;
    if (isShort) {
        AddMenuEntry(menu, entry++, 0, 6);
        if (func_ov001_02064ac0()) {
            AddMenuEntry(menu, entry++, 2, 9);
        }
        AddMenuEntry(menu, entry++, 4, 0);
        AddMenuEntry(menu, entry++, 6, -2);
        SetSelectionIfChanged_020bc92c(1);
    } else {
        int flagIndex;
        BOOL hasAnyFlag = FALSE;
        BOOL hasReports;
        BOOL hasJournal;

        hasReports = IsFlagSet(0xf5b);
        hasJournal = IsFlagSet(0xa0d);
        for (flagIndex = 0xf50; flagIndex <= 0x100f; flagIndex++) {
            if (IsGlobalPackedBitSet_02027304(flagIndex)) {
                hasAnyFlag = TRUE;
                break;
            }
        }
        if (hasReports) {
            AddMenuEntry(menu, entry++, 0, 1);
            AddMenuEntry(menu, entry++, 2, 2);
            AddMenuEntry(menu, entry++, 4, 3);
        }
        AddMenuEntry(menu, entry++, 6, 5);
        if (hasReports) {
            AddMenuEntry(menu, entry++, 8, 0xb);
        }
        if (hasJournal) {
            AddMenuEntry(menu, entry++, 10, 4);
        }
        if (hasAnyFlag) {
            AddMenuEntry(menu, entry++, 12, 0x12);
        }
        SetSelectionIfChanged_020bc92c(0);
    }
    menu->entryCount = entry - first;
    menu->cursor = func_ov039_020bc828();

    layoutContext = func_ov039_020bc18c();
    objManager = func_ov039_020bc1bc();
    config = data_ov074_020c5940;
    isResuming = menu->mode == 2;
    config.resource = func_ov039_020bc220(0, 7);
    InitObjManagerAndMark_020b9060(objManager, &config);
    func_ov027_020b8f98(objManager, func_ov039_020bc220(0, 8), 0x18);
    if (menu->isFullMenu) {
        resource = func_ov039_020bc220(0, 6);
    } else {
        resource = func_ov039_020bc220(2, 2);
    }
    func_ov027_020b7e24(layoutContext, resource);

    elementId = 6;
    for (i = 0; i < 8; i++) {
        pair = &menu->itemElements[i];
        pair->icon = func_ov027_020b90a4(objManager, elementId++);
        pair->text = func_ov027_020b90a4(objManager, elementId++);
        func_ov027_020b97b8(objManager, pair->icon, 3);
        func_ov027_020b97b8(objManager, pair->text, 3);
        if (i >= menu->entryCount) {
            func_ov027_020b9580(objManager, pair->icon, FALSE);
            func_ov027_020b9580(objManager, pair->text, FALSE);
        }
    }
    menu->cursorElement = func_ov027_020b90a4(objManager, 5);
    func_ov027_020b9580(objManager, menu->cursorElement, !isResuming);
    menu->frameElement = func_ov027_020b90a4(objManager, 0x16);
    menu->headerElement = func_ov027_020b90a4(objManager, 0);
    func_ov027_020b97b8(objManager, menu->frameElement, 1);
    func_ov027_020b97b8(objManager, menu->headerElement, 1);
    elementId = 1;
    for (arrow = 0; arrow < 2; arrow++) {
        menu->arrowsLeft[arrow] = func_ov027_020b90a4(objManager, elementId++);
        menu->arrowsRight[arrow] = func_ov027_020b90a4(objManager, elementId++);
        func_ov027_020b97b8(objManager, menu->arrowsLeft[arrow], 1);
        func_ov027_020b97b8(objManager, menu->arrowsRight[arrow], 1);
    }

    if (!menu->isFullMenu) {
        func_ov039_020bc318(0, 5, -1, 10, -1, 0);
        func_ov039_020bc414(1, 1, 0x2c0);
    } else {
        func_ov039_020bc318(0, 4, 0, 1, 2, func_ov039_020bc914());
        func_ov039_020bc414(1, 0, 0xc0);
    }
    menu->objManager = objManager;
    menu->layoutContext = layoutContext;

    if (isResuming) {
        func_ov027_020b9580(objManager, menu->headerElement, TRUE);
        func_ov027_020b9580(menu->objManager, func_ov027_020b90a4(menu->objManager, 0x17), TRUE);
        menu->state = 1;
        menu->mode = 2;
        SetSecondaryElementEnabled_020bc084(FALSE);
        func_ov039_020bc03c(0);
    }

    if (menu->isFullMenu) {
        BOOL hasKeyblade;
        int palette;
        void *file;
        int slot;
        u8 *record;

        hasKeyblade = HasAnyKeyblade();
        palette = hasKeyblade ? 2 : 5;
        file = func_0202c48c(data_ov074_020c59ec, 0xe);
        menu->textureKeyA = Msg_OpenContainerAndReadHeader_0202cc6c(data_ov074_020c59fc, 0xe, TRUE);
        menu->textureKeyB = Msg_OpenContainerAndReadHeader_0202cc6c(data_ov074_020c5a08, 0xe, TRUE);
        func_0202ed3c(&menu->model, data_ov074_020c5a18, file, 0xe);
        func_0202e9ec(menu->animA, &menu->model,
                      ((menu->textureKeyA + 0x8000) & 0xfffffc) << 7 | 0x80000000 | (palette & 0x1ff), 0xe);
        NNSi_FndFreeFromDefaultHeap_0202a1c4(file);

        func_ov021_020a9524();
        slot = 0;
        func_ov021_020a9598(slot);
        func_ov021_020a98e8(menu->weapon, slot);
        record = GetOverlaySelectionRecord(slot);
        params.kind = record[0x11];
        params.unk_04 = slot;
        params.unk_08 = slot;
        params.attachSlot = &menu->attachSlots[slot];
        params.scale = 0x100;
        params.unk_14 = slot;
        func_ov021_020a998c(menu->weapon, &params);
        func_ov021_020a95b4();
        func_0202e9ec(menu->animB, menu->weaponModel,
                      ((menu->textureKeyB + 0x8000) & 0xfffffc) << 7 | 0x80000000 | (palette & 0x1ff), 0xe);

        menu->jointIndexA = FindNode(menu, data_ov074_020c5930);
        menu->jointIndexB = FindNode(menu, data_ov074_020c5920);
        menu->model.renderObj.userData = menu;
        ClearSbcCallback_020188b8(&menu->model.renderObj);
        RegisterSbcCallback_020188a4(&menu->model.renderObj, func_ov074_020c50b0, NULL, 6, 3);
        func_02006d3c(-0x3b);
        LoadDefaultProjectionValues_0202a7b4(menu->projection);
        menu->projection[10] = 0x3000;
        menu->model.positionY -= 0xa00;
        selectJointAnimationBlend_0202f2cc(&menu->model, 0, menu->animA, 0);
        selectJointAnimationBlend_0202f2cc(&menu->model, 3, menu->model.blendTable, 0);
        func_0202f4e8(&menu->model);
        selectJointAnimationBlend_0202f2cc(menu->weaponModel, 0, menu->animB, 0);
        SetBit1WhenBit0Set_020a9ce8(menu->weapon, 1);
        func_ov021_020a9d28(menu->weapon, 0);
        menu->isWeaponLocked = !hasKeyblade;
    }

    menu->state = 2;
    if (!data_ov001_020a0460->bgmLocked) {
        u8 bgm = HasBgmOverride() ? 0x27 : func_ov001_02068094(data_0205fe0c->areaId);
        func_0204d8b8(bgm, 10);
    } else {
        func_0204d7f4(3);
    }
    return 1;
}
