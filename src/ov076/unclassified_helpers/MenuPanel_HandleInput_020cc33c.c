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

typedef struct ItemDef {
    u32 handle;
    s32 kind;
} ItemDef;

typedef struct ItemStock {
    u16 total;
    u16 used;
    s16 recordIndex;
    u8 pad_06[2];
    ItemDef *def;
} ItemStock;

typedef union TouchPoint {
    u32 raw;
    struct {
        s16 x;
        s16 y;
    } pos;
} TouchPoint;

typedef struct PadState {
    u8 pad_00[4];
    TouchPoint touch;
    u16 held;
    u16 trigger;
} PadState;

typedef struct ListPosition {
    fx32 x;
    fx32 y;
} ListPosition;

typedef struct Widget {
    u8 pad_00[0x94];
    u32 lowFlag : 1;
    u32 visible : 1;
} Widget;

typedef struct CursorElement {
    u8 pad_00[0x14];
    int index;
} CursorElement;

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
    s32 hideHint;
    u8 pad_00034[0x3c18 - 0x34];
    ItemStock *items[(0x4d84 - 0x3c18) / 4];
    ScrollList list;
    u8 pad_04E50[0x4e58 - 0x4e50];
    s32 selectedIndex;
    u8 pad_04E5C[0x7f90 - 0x4e5c];
    PadState *pad;
    u8 pad_07F94[0x11e1a - 0x7f94];
    u16 inputLock;
    u8 pad_11E1C[0x11e3c - 0x11e1c];
    s32 owner;
    u8 pad_11E40[4];
    CursorElement *cursorElement;
    void *scrollElement;
    u8 pad_11E4C[0x11e64 - 0x11e4c];
    u8 ownedFlags[0x40];
} MenuPanel;

extern u16 data_02060500;

extern BOOL func_ov039_020bc0d4(void);
extern BOOL func_ov039_020bc0ec(void);
extern PadState *func_ov039_020bca00(void);
extern Widget *FindWidgetById_020b90a4(void *container, int id);
extern void SetContainerElementVisible_020ccce8(void *container, int elementId, BOOL visible);
extern int MenuPanel_Close_020ca970(MenuPanel *panel);
extern BOOL MenuPanel_SetFilterMode_020ca1dc(MenuPanel *panel, int mode);
extern void SetupScrollList_020bdf10(ScrollList *list, void *container, BOOL enabled);
extern BOOL ScrollList_HandleInput_020be0c4(ScrollList *list, void *container);
extern void func_0204f204(void *container, int index, int value);
extern int MenuPanel_ConfirmSelection_020ca988(MenuPanel *panel);
extern int func_ov076_020ca8c0(MenuPanel *panel);
extern BOOL ItemList_IsRewardEntryLocked_020cab38(ItemStock *entry);
extern int func_ov076_020ca8dc(MenuPanel *panel);
extern BOOL PlaySoundEffect_0204d924(int seqArcNo, int index);
extern u16 MenuPanel_ApplyCategoryFilter_020c9c14(MenuPanel *panel, int mode);
extern void SetStatusPageAndCursor_020c2ca4(int page, int index);
extern void ItemList_UpdateHeaderText_020c95cc(MenuPanel *panel);
extern void RefreshScrollListLayout_020be138(ScrollList *list, void *container);
extern void func_ov076_020c9d98(MenuPanel *panel);
extern void func_ov027_020b91c8(void *container, void *element, ListPosition *pos, int mode);
extern ListPosition *func_ov027_020b9360(void *container, void *element, ListPosition *pos, int mode);
extern void SetPackedBit(u8 *bits, int index);

static inline void MenuPanel_SyncCursor(MenuPanel *panel)
{
    void *container = panel->container;
    int row;
    ListPosition pos;

    row = panel->list.cursor;
    if (row < 0) {
        row = 0;
    }
    pos.y = ((row - panel->list.topIndex) * 16 - (panel->list.scrollPixels & 0xf)) << 12;
    func_ov027_020b91c8(container, panel->scrollElement, &pos, 5);
    func_ov027_020b91c8(container, panel->cursorElement, func_ov027_020b9360(container, panel->scrollElement, &pos, 0), 0);
    if (panel->list.cursor >= 0 && panel->list.cursor < panel->list.itemCount) {
        SetPackedBit(panel->ownedFlags, panel->items[panel->list.cursor]->def->handle);
        panel->selectedIndex = panel->list.cursor;
    }
}

int MenuPanel_HandleInput_020cc33c(MenuPanel *panel)
{
    BOOL changed = FALSE;
    u16 repeat;
    int prevCursor;
    BOOL moved = FALSE;
    BOOL redraw = FALSE;
    BOOL inactive;
    u16 trigger;
    u16 held;
    TouchPoint touch;
    int touchRow;
    int mode;
    int result;

    inactive = !func_ov039_020bc0d4();
    if (func_ov039_020bc0ec()) {
        if (((data_02060500 & 0x400) && (func_ov039_020bca00()->held & 3) == 0) || (!inactive && panel->hideHint)) {
            panel->hideHint ^= 1;
            if (FindWidgetById_020b90a4(panel->container, 3)->visible) {
                SetContainerElementVisible_020ccce8(panel->container, 5, panel->hideHint == 0);
            }
        }
    }
    trigger = (inactive || panel->inputLock != 0) ? 0 : data_02060500;
    if (panel->state == 0) {
        return 0;
    }
    if (!func_ov039_020bc0d4()) {
        return 1;
    }
    if (panel->inputLock != 0) {
        repeat = 0;
        held = 0;
        touch.raw = repeat;
    } else {
        repeat = panel->inputLock ? 0 : panel->pad->trigger;
        held = panel->pad->held;
        touch = panel->pad->touch;
    }
    if (panel->closing == 0 && (held & 3) == 1 && touch.pos.y < 0xaf) {
        if (touch.pos.x < 0x50) {
            return MenuPanel_Close_020ca970(panel);
        }
        if (touch.pos.y >= 8 && touch.pos.y < 0x18) {
            s16 edge = 0x70;

            panel->busy = 1;
            if (touch.pos.x < edge) {
                changed = MenuPanel_SetFilterMode_020ca1dc(panel, 0);
            } else {
                edge += 0x20;
                if (touch.pos.x < edge) {
                    changed = MenuPanel_SetFilterMode_020ca1dc(panel, 1);
                } else {
                    mode = 2;
                    do {
                        edge += 0x10;
                        if (touch.pos.x < edge) {
                            changed = MenuPanel_SetFilterMode_020ca1dc(panel, mode);
                            break;
                        }
                        mode++;
                    } while (edge < 0x100);
                }
            }
            if (changed) {
                SetupScrollList_020bdf10(&panel->list, panel->container, TRUE);
            }
            panel->busy = 0;
            return 1;
        }
    }
    if (panel->closing == 0) {
        if (panel->inputLock != 0) {
            panel->inputLock--;
        }
        prevCursor = panel->list.cursor;
        if (ScrollList_HandleInput_020be0c4(&panel->list, panel->container) || (repeat & 0xf0)) {
            moved = TRUE;
            redraw = TRUE;
            func_0204f204(panel->container, panel->cursorElement->index, 0);
        }
        if (panel->list.touchIndex < 0) {
            touchRow = -1;
        } else {
            touchRow = panel->list.touchIndex / panel->list.rowHeight;
        }
        if ((trigger & 1) || (touchRow >= 0 && (held & 3) == 2 && touchRow == prevCursor)) {
            result = MenuPanel_ConfirmSelection_020ca988(panel);
            if (result != 1) {
                return result;
            }
        } else if (trigger & 0xa) {
            return MenuPanel_Close_020ca970(panel);
        } else if (trigger & 0x800) {
            if (panel->list.cursor < panel->list.itemCount) {
                ItemStock *entry = panel->items[panel->list.cursor];
                BOOL unused = FALSE;
                BOOL usable = TRUE;

                if (entry->def->kind != 3 && entry->def->kind != 2) {
                    usable = FALSE;
                }
                if (usable && entry->used == 0) {
                    unused = TRUE;
                }
                if (unused) {
                    return func_ov076_020ca8c0(panel);
                }
                if (ItemList_IsRewardEntryLocked_020cab38(entry)) {
                    return func_ov076_020ca8dc(panel);
                }
            }
            PlaySoundEffect_0204d924(1, 4);
        } else if (trigger & 0x200) {
            if (panel->isEmpty == 0) {
                s16 category = panel->category;

                panel->busy = 1;
                do {
                    category--;
                    if (category < 0) {
                        category = 7;
                    }
                } while (category != 1 && panel->category != category && MenuPanel_ApplyCategoryFilter_020c9c14(panel, category) == 0);
                changed = MenuPanel_SetFilterMode_020ca1dc(panel, category);
            }
        } else if (trigger & 0x100) {
            if (panel->isEmpty == 0) {
                s16 category = panel->category;

                panel->busy = 1;
                do {
                    category++;
                    if (category == 8) {
                        category = 0;
                    }
                } while (category != 1 && panel->category != category && MenuPanel_ApplyCategoryFilter_020c9c14(panel, category) == 0);
                changed = MenuPanel_SetFilterMode_020ca1dc(panel, category);
            }
        } else if (panel->list.cursor >= 0 && panel->list.cursor < panel->list.itemCount) {
            int handle = panel->items[panel->list.cursor]->def->handle;
            int page = 5;

            switch (panel->owner) {
            case 0:
                if (handle >= 0x90) {
                    if (handle < 0xa6 || handle == 0xca) {
                        page = 0;
                    } else if (handle < 0xd0) {
                        page = 2;
                    }
                }
                break;
            case 1:
            case 2:
                if (handle < 0x90) {
                    page = 1;
                }
                break;
            case 3:
                if (handle >= 0xd0 && handle < 0x110) {
                    page = 4;
                }
                break;
            case 4:
                if (handle >= 0x120 && handle < 0x160) {
                    page = 2;
                }
                break;
            }
            if (page != 5) {
                SetStatusPageAndCursor_020c2ca4(page, -1);
            }
        }
        if ((repeat & 0xf0) || (trigger & 0x300)) {
            ItemList_UpdateHeaderText_020c95cc(panel);
            if (changed) {
                SetupScrollList_020bdf10(&panel->list, panel->container, TRUE);
            } else {
                RefreshScrollListLayout_020be138(&panel->list, panel->container);
            }
            redraw = TRUE;
        }
        if (!changed) {
            if (moved) {
                func_ov076_020c9d98(panel);
            }
            if (redraw) {
                MenuPanel_SyncCursor(panel);
            }
        } else {
            MenuPanel_SyncCursor(panel);
            func_ov076_020c9d98(panel);
        }
        panel->busy = 0;
    }
    return 1;
}
