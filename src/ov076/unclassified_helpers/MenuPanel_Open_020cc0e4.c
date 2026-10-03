#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct ScrollList {
    s16 itemCount;
    s16 cursor;
    s16 topIndex;
    u8 scrollOffset;
    u8 visibleRows;
    u8 rowHeight;
    u8 pad_09[7];
    s32 suppressRefresh;
    u8 pad_14[8];
    u8 dragState;
    u8 pad_1d;
    s16 baseY;
    s16 touchIndex;
    u8 pad_22[6];
    s16 trackTop;
    s16 trackBottom;
    u8 pad_2c[8];
    s32 scrollPixels;
    s32 dragOffset;
    u8 trackRows;
    u8 entryCount;
    u8 pad_3e[2];
    void *upArrow;
    void *downArrow;
    void *thumb;
    void *slots[16];
    void *entries[16];
} ScrollList;

typedef struct ItemEntry {
    u8 pad_00[8];
    const int *recordId;
} ItemEntry;

typedef struct PadState {
    u8 pad_00[0xa];
    u16 repeat;
} PadState;

typedef struct CategorySet {
    u32 count;
    u32 categories[4];
} CategorySet;

typedef struct ListPosition {
    fx32 x;
    fx32 y;
} ListPosition;

typedef struct SaveData {
    u8 pad_0000[0x2bd8];
    u8 ownedFlags[0x40];
} SaveData;

typedef struct MenuPanel {
    s32 mode;
    s32 state;
    s32 timer;
    u8 pad_0000C[0xc];
    void *container;
    u8 pad_0001C[4];
    u16 category;
    u8 pad_00022[2];
    s32 isEmpty;
    u8 pad_00028[0x3c18 - 0x28];
    ItemEntry *items[(0x4d84 - 0x3c18) / 4];
    ScrollList list;
    u8 pad_04E50[0x4e58 - 0x4e50];
    s32 selectedIndex;
    u8 pad_04E5C[0x7290 - 0x4e5c];
    u16 screen[0x340];
    u8 pad_07910[0x7f90 - 0x7910];
    PadState *pad;
    u8 pad_07F94[0x11e1a - 0x7f94];
    u16 inputLock;
    u8 pad_11E1C[0x11e24 - 0x11e1c];
    u8 customCategoryCount;
    u8 pad_11E25[3];
    u32 customCategories[4];
    u8 pad_11E38[4];
    s32 owner;
    u8 pad_11E40[4];
    void *cursorElement;
    void *scrollElement;
    u8 pad_11E4C[0x11e60 - 0x11e4c];
    u16 savedFlags;
    u8 pad_11E62[2];
    u8 ownedFlags[0x40];
    u8 pad_11EA4[0x11eb4 - 0x11ea4];
    s32 pendingAction;
} MenuPanel;

extern const CategorySet data_ov076_020cd190[];
extern const char data_ov076_020cd35c[];
extern u16 data_02060500;
extern SaveData *data_0205fe0c;

extern void *func_ov027_020b90a4(void *container, int elementId);
extern void *G2_GetBG1CharPtr_020070cc(void);
extern void *G2_GetBG1ScrPtr_02006e34(void);
extern void MIi_CpuClearFast_01ff8740(u32 data, void *dest, u32 size);
extern void func_01ff869c(const void *src, void *dest, u32 size);
extern void func_01ff8ad8(const void *src, void *dest, u32 size);
extern void MIi_CpuCopy32_01ff8710(const void *src, void *dest, u32 size);
extern u16 func_ov039_020bc670(void);
extern void SetStateFlagBits_020bc688(u8 clearMask, u8 setBits);
extern void SetNavigationElementsVisible_020ccd30(void *container, BOOL visible);
extern void SetContainerElementVisible_020ccce8(void *container, int elementId, BOOL visible);
extern u16 MenuPanel_ApplyCategoryFilter_020c9c14(MenuPanel *panel, int mode);
extern void func_ov027_020b96a0(void *container, void *element, u16 mode);
extern void SetupScrollList_020bdf10(ScrollList *list, void *container, BOOL enabled);
extern void RefreshScrollListLayout_020be138(ScrollList *list, void *container);
extern void InvokeForChannelOrBoth_0200110c(u32 irqMask, const char *name, void (*callback)(void), int channel);
extern void func_ov076_020cac94(void);
extern void func_ov076_020c9d98(MenuPanel *panel);
extern void func_ov027_020b91c8(void *container, void *element, ListPosition *pos, int mode);
extern ListPosition *func_ov027_020b9360(void *container, void *element, ListPosition *pos, int mode);
extern void SetPackedBit(u8 *bits, int index);
extern void PlaySoundEffect_0204d924(int seqArcNo, int index);

static inline int GetVisiblePlane(void)
{
    return (*(vu32 *)0x04000000 & 0x1f00) >> 8;
}

static inline void SetVisiblePlane(int plane)
{
    *(vu32 *)0x04000000 = (*(vu32 *)0x04000000 & ~0x1f00) | (plane << 8);
}

void MenuPanel_Open_020cc0e4(MenuPanel *panel, int owner)
{
    const CategorySet *set;
    void *container;
    int row;
    ListPosition pos;

    if (panel->state != 0) {
        return;
    }
    set = &data_ov076_020cd190[owner];
    container = panel->container;
    func_ov027_020b90a4(container, 0);
    MIi_CpuClearFast_01ff8740(0, G2_GetBG1CharPtr_020070cc(), 0x5040);
    func_01ff869c(panel->screen, G2_GetBG1ScrPtr_02006e34(), 0x680);
    panel->savedFlags = func_ov039_020bc670();
    SetStateFlagBits_020bc688(1, 0);
    SetNavigationElementsVisible_020ccd30(container, FALSE);
    SetContainerElementVisible_020ccce8(container, 7, TRUE);
    SetContainerElementVisible_020ccce8(container, 0x1b, TRUE);
    SetContainerElementVisible_020ccce8(container, 0x1c, TRUE);
    SetContainerElementVisible_020ccce8(container, 0, TRUE);
    SetContainerElementVisible_020ccce8(container, 1, TRUE);
    panel->customCategoryCount = set->count;
    func_01ff8ad8(set->categories, panel->customCategories, sizeof(set->categories));

    for (;;) {
        panel->list.itemCount = MenuPanel_ApplyCategoryFilter_020c9c14(panel, panel->category);
        if (panel->category == 0) {
            panel->isEmpty = panel->list.itemCount == 0;
            break;
        }
        if (panel->list.itemCount != 0 || panel->category == 1) {
            break;
        }
        panel->category = 0;
    }

    func_ov027_020b96a0(panel->container, func_ov027_020b90a4(panel->container, 0x1b), panel->category);
    panel->list.visibleRows = 9;
    panel->list.baseY = -16;
    SetupScrollList_020bdf10(&panel->list, container, TRUE);
    RefreshScrollListLayout_020be138(&panel->list, panel->container);
    panel->state = 1;
    panel->timer = 0;
    panel->pendingAction = 0;
    panel->inputLock = 2;
    InvokeForChannelOrBoth_0200110c(1, data_ov076_020cd35c, func_ov076_020cac94, 0);
    func_ov076_020c9d98(panel);
    data_02060500 = 0;
    panel->pad->repeat = 0;
    panel->owner = owner;
    MIi_CpuCopy32_01ff8710(data_0205fe0c->ownedFlags, panel->ownedFlags, 0x40);
    panel->selectedIndex = -1;

    container = panel->container;
    row = 0;
    if (panel->list.cursor >= 0) {
        row = panel->list.cursor;
    }
    pos.y = ((row - panel->list.topIndex) * 16 - (panel->list.scrollPixels & 0xf)) << 12;
    func_ov027_020b91c8(container, panel->scrollElement, &pos, 5);
    func_ov027_020b91c8(container, panel->cursorElement, func_ov027_020b9360(container, panel->scrollElement, &pos, 0), 0);
    if (panel->list.cursor >= 0 && panel->list.cursor < panel->list.itemCount) {
        SetPackedBit(panel->ownedFlags, *panel->items[panel->list.cursor]->recordId);
        panel->selectedIndex = panel->list.cursor;
    }
    SetVisiblePlane(GetVisiblePlane() | 2);
    if (panel->mode == 0) {
        PlaySoundEffect_0204d924(1, 2);
    }
}
