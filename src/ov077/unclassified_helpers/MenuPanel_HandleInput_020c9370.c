#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct ScrollList {
    s16 itemCount;
    s16 cursor;
    s16 topIndex;
    u8 scrollOffset;
    u8 visibleRows;
    u8 rowHeight;
    u8 pad_09[0x20 - 0x9];
    s16 touchIndex;
    u8 pad_22[0x34 - 0x22];
    s32 scrollPixels;
    u8 pad_38[0xcc - 0x38];
} ScrollList;

typedef struct ItemDef {
    s32 recordId;
    s32 kind;
} ItemDef;

typedef struct ItemEntry {
    u16 count;
    u16 used;
    u8 pad_04[4];
    ItemDef *def;
} ItemEntry;

typedef struct TouchPoint {
    s16 x;
    s16 y;
} TouchPoint;

typedef union TouchPos {
    u32 raw;
    TouchPoint at;
} TouchPos;

typedef struct PanelInput {
    u8 pad_00[4];
    TouchPos pos;
    u16 state;
    u16 trigger;
} PanelInput;

typedef struct TouchState {
    u8 pad_00[8];
    u16 state;
} TouchState;

typedef struct Widget {
    u8 pad_00[0x14];
    int handle;
    u8 pad_18[0x94 - 0x18];
    u32 unk_94_0 : 1;
    u32 enabled : 1;
} Widget;

typedef struct ListPosition {
    fx32 x;
    fx32 y;
} ListPosition;

typedef struct MenuPanel {
    s32 mode;
    s32 state;
    s32 closing;
    u8 pad_0000C[0xc];
    void *container;
    u8 pad_0001C[4];
    u16 category;
    u8 pad_00022[2];
    s32 isEmpty;
    u8 pad_00028[4];
    s32 busy;
    s32 hideSort;
    u8 pad_00034[0x3c18 - 0x34];
    ItemEntry *items[(0x4d84 - 0x3c18) / 4];
    ScrollList list;
    u8 pad_04E50[0x4e58 - 0x4e50];
    s32 selectedIndex;
    u8 pad_04E5C[0x7f90 - 0x4e5c];
    PanelInput *input;
    u8 pad_07F94[0x11e1a - 0x7f94];
    u16 inputLock;
    u8 pad_11E1C[0x11e3c - 0x11e1c];
    s32 owner;
    u8 pad_11E40[4];
    Widget *cursorElement;
    void *scrollElement;
    u8 pad_11E4C[0x11e64 - 0x11e4c];
    u8 ownedFlags[0x40];
} MenuPanel;

extern u16 data_02060500;

extern BOOL func_ov039_020bc0d4(void);
extern BOOL func_ov039_020bc0ec(void);
extern TouchState *func_ov039_020bca00(void);
extern Widget *FindWidgetById_020b90a4(void *container, int id);
extern void SetContainerElementVisible_020c9d1c(void *container, int elementId, BOOL visible);
extern int CancelAndCloseMenu_020c79a4(MenuPanel *panel);
extern BOOL MenuPanel_SetFilterMode_020c7210(MenuPanel *panel, int mode);
extern void SetupScrollList_020bdf10(ScrollList *list, void *container, BOOL enabled);
extern BOOL ScrollList_Update_020be0c4(ScrollList *list, void *container);
extern void func_0204f204(void *container, int handle, int palette);
extern int MenuPanel_ConfirmSelection_020c79bc(MenuPanel *panel);
extern int func_ov077_020c78f4(MenuPanel *panel);
extern BOOL CanUseItemEntry_020c7b6c(ItemEntry *entry);
extern int func_ov077_020c7910(MenuPanel *panel);
extern void PlaySoundEffect_0204d924(int seqArcNo, int index);
extern BOOL MenuPanel_ApplyCategoryFilter_020c6c48(MenuPanel *panel, int mode);
extern void SetStatusPageAndCursor_020c2ca4(int page, int index);
extern void ItemList_UpdateHeaderText_020c6600(MenuPanel *panel);
extern void RefreshScrollListLayout_020be138(ScrollList *list, void *container);
extern void func_ov077_020c6dcc(MenuPanel *panel);
extern void func_ov027_020b91c8(void *container, void *element, ListPosition *pos, int mode);
extern ListPosition *func_ov027_020b9360(void *container, void *element, ListPosition *pos, int mode);
extern void SetPackedBit(u8 *bits, int index);

static inline void SyncCursorMarker(MenuPanel *panel)
{
    void *container = panel->container;
    int row = panel->list.cursor;
    ListPosition pos;

    if (row < 0) {
        row = 0;
    }
    pos.y = ((row - panel->list.topIndex) * 16 - (panel->list.scrollPixels & 0xf)) << 12;
    func_ov027_020b91c8(container, panel->scrollElement, &pos, 5);
    func_ov027_020b91c8(container, panel->cursorElement, func_ov027_020b9360(container, panel->scrollElement, &pos, 0), 0);
    if (panel->list.cursor >= 0 && panel->list.cursor < panel->list.itemCount) {
        SetPackedBit(panel->ownedFlags, panel->items[panel->list.cursor]->def->recordId);
        panel->selectedIndex = panel->list.cursor;
    }
}

int MenuPanel_HandleInput_020c9370(MenuPanel *panel)
{
    TouchPos pos;
    u16 trigger;
    s16 prevCursor;
    BOOL selectionChanged;
    BOOL layoutChanged;
    BOOL changed;
    BOOL idle;
    u16 keys;
    u16 state;
    BOOL closing;
    u16 lock;
    int hit;

    changed = FALSE;
    selectionChanged = FALSE;
    layoutChanged = FALSE;

    idle = !func_ov039_020bc0d4();
    if (func_ov039_020bc0ec()) {
        if (((data_02060500 & 0x400) && (func_ov039_020bca00()->state & 3) == 0) || (!idle && panel->hideSort != 0)) {
            panel->hideSort ^= 1;
            if (FindWidgetById_020b90a4(panel->container, 3)->enabled) {
                SetContainerElementVisible_020c9d1c(panel->container, 5, panel->hideSort == 0);
            }
        }
    }
    keys = (idle || panel->inputLock != 0) ? 0 : data_02060500;
    if (panel->state == 0) {
        return 0;
    }
    if (!func_ov039_020bc0d4()) {
        return 1;
    }
    lock = panel->inputLock;
    if (lock != 0) {
        trigger = 0;
        state = 0;
        pos.raw = trigger;
    } else {
        trigger = lock != 0 ? 0 : panel->input->trigger; /* redundant lock test matches original codegen */
        state = panel->input->state;
        pos = panel->input->pos;
    }
    closing = panel->closing;
    if (closing == 0 && (state & 3) == 1 && pos.at.y < 0xaf) {
        if (pos.at.x < 0x50) {
            return CancelAndCloseMenu_020c79a4(panel);
        }
        if (pos.at.y >= 8 && pos.at.y < 0x18) {
            int tab = 1;
            s16 edge = 0x70;

            panel->busy = TRUE;
            if (pos.at.x < edge) {
                changed = MenuPanel_SetFilterMode_020c7210(panel, 0);
            } else {
                edge += 0x20;
                if (pos.at.x < edge) {
                    changed = MenuPanel_SetFilterMode_020c7210(panel, tab);
                } else {
                    tab = 2;
                    do {
                        edge += 0x10;
                        if (edge > pos.at.x) {
                            changed = MenuPanel_SetFilterMode_020c7210(panel, tab);
                            break;
                        }
                        tab++;
                    } while (edge < 0x100);
                }
            }
            if (changed) {
                SetupScrollList_020bdf10(&panel->list, panel->container, TRUE);
            }
            panel->busy = FALSE;
            return 1;
        }
    }
    if (closing != 0) {
        goto end;
    }
    if (lock != 0) {
        panel->inputLock--;
    }
    prevCursor = panel->list.cursor;
    if (ScrollList_Update_020be0c4(&panel->list, panel->container) || (trigger & 0xf0)) {
        selectionChanged = TRUE;
        layoutChanged = TRUE;
        func_0204f204(panel->container, panel->cursorElement->handle, 0);
    }
    if (panel->list.touchIndex < 0) {
        hit = -1;
    } else {
        hit = panel->list.touchIndex / panel->list.rowHeight;
    }
    if ((keys & 1) || (hit >= 0 && (state & 3) == 2 && hit == prevCursor)) {
        int result = MenuPanel_ConfirmSelection_020c79bc(panel);
        if (result != 1) {
            return result;
        }
    } else if (keys & 0xa) {
        return CancelAndCloseMenu_020c79a4(panel);
    } else if (keys & 0x800) {
        if (panel->list.cursor < panel->list.itemCount) {
            ItemEntry *entry = panel->items[panel->list.cursor];
            BOOL direct = FALSE;
            BOOL special = TRUE;

            if (entry->def->kind != 3 && entry->def->kind != 2) {
                special = FALSE;
            }
            if (special && entry->used == 0) {
                direct = TRUE;
            }
            if (direct) {
                return func_ov077_020c78f4(panel);
            }
            if (CanUseItemEntry_020c7b6c(entry)) {
                return func_ov077_020c7910(panel);
            }
        }
        PlaySoundEffect_0204d924(1, 4);
    } else if (keys & 0x200) {
        if (panel->isEmpty == 0) {
            s16 mode = panel->category;

            panel->busy = TRUE;
            do {
                mode--;
                if (mode < 0) {
                    mode = 7;
                }
            } while (mode != 1 && panel->category != mode && !MenuPanel_ApplyCategoryFilter_020c6c48(panel, mode));
            changed = MenuPanel_SetFilterMode_020c7210(panel, mode);
        }
    } else if (keys & 0x100) {
        if (panel->isEmpty == 0) {
            s16 mode = panel->category;

            panel->busy = TRUE;
            do {
                mode++;
                if (mode == 8) {
                    mode = 0;
                }
            } while (mode != 1 && panel->category != mode && !MenuPanel_ApplyCategoryFilter_020c6c48(panel, mode));
            changed = MenuPanel_SetFilterMode_020c7210(panel, mode);
        }
    } else if (panel->list.cursor >= 0 && panel->list.cursor < panel->list.itemCount) {
        int recordId = panel->items[panel->list.cursor]->def->recordId;
        int page = 5;

        switch (panel->owner) {
        case 0:
            if (recordId >= 0x90) {
                if (recordId < 0xa6 || recordId == 0xca) {
                    page = 0;
                } else if (recordId < 0xd0) {
                    page = 2;
                }
            }
            break;
        case 1:
        case 2:
            if (recordId < 0x90) {
                page = 1;
            }
            break;
        case 3:
            if (recordId >= 0xd0 && recordId < 0x110) {
                page = 4;
            }
            break;
        case 4:
            if (recordId >= 0x120 && recordId < 0x160) {
                page = 2;
            }
            break;
        }
        if (page != 5) {
            SetStatusPageAndCursor_020c2ca4(page, -1);
        }
    }
    if ((trigger & 0xf0) || (keys & 0x300)) {
        ItemList_UpdateHeaderText_020c6600(panel);
        if (changed) {
            SetupScrollList_020bdf10(&panel->list, panel->container, TRUE);
        } else {
            RefreshScrollListLayout_020be138(&panel->list, panel->container);
        }
        layoutChanged = TRUE;
    }
    if (!changed) {
        if (selectionChanged) {
            func_ov077_020c6dcc(panel);
        }
        if (layoutChanged) {
            SyncCursorMarker(panel);
        }
    } else {
        SyncCursorMarker(panel);
        func_ov077_020c6dcc(panel);
    }
    panel->busy = FALSE;
end:
    return 1;
}
