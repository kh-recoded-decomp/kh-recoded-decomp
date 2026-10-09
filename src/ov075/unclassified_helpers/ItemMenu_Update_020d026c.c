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
    s32 id;
    s32 kind;
} ItemDef;

typedef struct ItemSlot {
    u16 id;
    u16 count;
    u8 pad_04[4];
    ItemDef *def;
} ItemSlot;

typedef struct TouchPos {
    s16 x;
    s16 y;
} TouchPos;

typedef union TouchWord {
    u32 raw;
    TouchPos pos;
} TouchWord;

typedef struct PadState {
    u8 pad_00[4];
    TouchWord touch;
    u16 trigger;
    u16 repeat;
} PadState;

typedef struct ListPosition {
    fx32 x;
    fx32 y;
} ListPosition;

typedef struct LayoutElement {
    u8 pad_00[0x14];
    int animId;
} LayoutElement;

typedef struct Widget {
    u8 pad_00[0x94];
    u32 unk_0 : 1;
    u32 enabled : 1;
} Widget;

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
    u8 pad_00028[4];
    s32 busy;
    s32 hideHelp;
    u8 pad_00034[0x3c18 - 0x34];
    ItemSlot *items[(0x4d84 - 0x3c18) / 4];
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
    LayoutElement *cursorElement;
    void *scrollElement;
    u8 pad_11E4C[0x11e64 - 0x11e4c];
    int ownedFlags[0x10];
} MenuPanel;

extern u16 data_02060500;

extern int func_ov039_020bc0d4(void);
extern int func_ov039_020bc0ec(void);
extern PadState *func_ov039_020bca00(void);
extern Widget *FindWidgetById_020b90a4(void *container, int id);
extern void SetLayoutElementVisible_020d0e4c(void *container, s32 elementId, BOOL visible);
extern s32 CancelItemPicker_020ceb60(MenuPanel *panel);
extern s32 ConfirmItemPicker_020ceb78(MenuPanel *panel);
extern BOOL SelectItemTab_020ce3cc(MenuPanel *panel, int tab);
extern int BuildTabItemList_020cde04(MenuPanel *panel, int tab);
extern void SetupScrollList_020bdf10(ScrollList *list, void *container, BOOL enabled);
extern void RefreshScrollListLayout_020be138(ScrollList *list, void *container);
extern int UpdateScrollList_020be0c4(ScrollList *list, void *container);
extern void func_0204f204(void *container, int animId, int frame);
extern int func_ov075_020ceab0(MenuPanel *panel);
extern int func_ov075_020ceacc(MenuPanel *panel);
extern BOOL IsRewardEntryLocked_020ced28(ItemSlot *slot);
extern void PlaySoundEffect_0204d924(int seqArcNo, int index);
extern void SetStatusPageAndCursor_020c2ca4(int page, int index);
extern void UpdateItemDescription_020cd384(MenuPanel *panel);
extern void func_ov075_020cdf88(MenuPanel *panel);
extern void func_ov027_020b91c8(void *container, void *element, ListPosition *pos, int mode);
extern ListPosition *func_ov027_020b9360(void *container, void *element, ListPosition *pos, int mode);
extern void SetPackedBit(int *bitWords, int bitIndex);

static inline void SyncCursorElement(MenuPanel *panel)
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
        SetPackedBit(panel->ownedFlags, panel->items[panel->list.cursor]->def->id);
        panel->selectedIndex = panel->list.cursor;
    }
}

int ItemMenu_Update_020d026c(MenuPanel *panel)
{
    u16 repeat;
    int prevCursor;
    BOOL changed = FALSE;
    BOOL scrolled = FALSE;
    BOOL refresh = FALSE;
    BOOL inactive;
    u16 pressed;
    u16 trigger;
    u16 lock;
    TouchWord touch;
    int touched;
    int result;
    int tab;
    s16 edge;
    s16 nextTab;

    inactive = func_ov039_020bc0d4() == 0;
    if (func_ov039_020bc0ec() != 0 &&
        (((data_02060500 & 0x400) && (func_ov039_020bca00()->trigger & 3) == 0) || (!inactive && panel->hideHelp != 0))) {
        panel->hideHelp ^= 1;
        if (FindWidgetById_020b90a4(panel->container, 3)->enabled) {
            SetLayoutElementVisible_020d0e4c(panel->container, 5, panel->hideHelp == 0);
        }
    }
    pressed = (inactive || panel->inputLock != 0) ? 0 : data_02060500;

    if (panel->state == 0) {
        return 0;
    }
    if (func_ov039_020bc0d4() == 0) {
        return 1;
    }

    lock = panel->inputLock;
    if (lock != 0) {
        repeat = 0;
        trigger = 0;
        touch.raw = repeat;
    } else {
        repeat = lock != 0 ? 0 : panel->pad->repeat;
        trigger = panel->pad->trigger;
        touch = panel->pad->touch;
    }

    if (panel->timer == 0 && (trigger & 3) == 1 && touch.pos.y < 0xaf) {
        if (touch.pos.x < 0x50) {
            return CancelItemPicker_020ceb60(panel);
        }
        if (touch.pos.y >= 8 && touch.pos.y < 0x18) {
            edge = 0x70;
            panel->busy = 1;
            if (touch.pos.x < edge) {
                changed = SelectItemTab_020ce3cc(panel, 0);
            } else {
                edge += 0x20;
                if (touch.pos.x < edge) {
                    changed = SelectItemTab_020ce3cc(panel, 1);
                } else {
                    tab = 2;
                    do {
                        edge += 0x10;
                        if (touch.pos.x < edge) {
                            changed = SelectItemTab_020ce3cc(panel, tab);
                            break;
                        }
                        tab++;
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
    if (panel->timer == 0) {
        if (lock != 0) {
            panel->inputLock--;
        }
        prevCursor = panel->list.cursor;
        if (UpdateScrollList_020be0c4(&panel->list, panel->container) != 0 || (repeat & 0xf0)) {
            scrolled = TRUE;
            refresh = TRUE;
            func_0204f204(panel->container, panel->cursorElement->animId, 0);
        }
        touched = panel->list.touchIndex < 0 ? -1 : panel->list.touchIndex / panel->list.rowHeight;

        if ((pressed & 1) || (touched >= 0 && (trigger & 3) == 2 && touched == prevCursor)) {
            result = ConfirmItemPicker_020ceb78(panel);
            if (result != 1) {
                return result;
            }
        } else if (pressed & 0xa) {
            return CancelItemPicker_020ceb60(panel);
        } else if (pressed & 0x800) {
            if (panel->list.cursor < panel->list.itemCount) {
                ItemSlot *slot = panel->items[panel->list.cursor];
                BOOL ready = FALSE;
                BOOL usable = TRUE;

                if (slot->def->kind != 3 && slot->def->kind != 2) {
                    usable = FALSE;
                }
                if (usable && slot->count == 0) {
                    ready = TRUE;
                }

                if (ready) {
                    return func_ov075_020ceab0(panel);
                }
                if (IsRewardEntryLocked_020ced28(slot)) {
                    return func_ov075_020ceacc(panel);
                }
            }
            PlaySoundEffect_0204d924(1, 4);
        } else if (pressed & 0x200) {
            if (panel->isEmpty == 0) {
                nextTab = panel->category;
                panel->busy = 1;
                do {
                    if (--nextTab < 0) {
                        nextTab = 7;
                    }
                } while (nextTab != 1 && panel->category != nextTab && BuildTabItemList_020cde04(panel, nextTab) == 0);
                changed = SelectItemTab_020ce3cc(panel, nextTab);
            }
        } else if (pressed & 0x100) {
            if (panel->isEmpty == 0) {
                nextTab = panel->category;
                panel->busy = 1;
                do {
                    if (++nextTab == 8) {
                        nextTab = 0;
                    }
                } while (nextTab != 1 && panel->category != nextTab && BuildTabItemList_020cde04(panel, nextTab) == 0);
                changed = SelectItemTab_020ce3cc(panel, nextTab);
            }
        } else if (panel->list.cursor >= 0 && panel->list.cursor < panel->list.itemCount) {
            int id = panel->items[panel->list.cursor]->def->id;
            int page = 5;

            switch (panel->owner) {
            case 0:
                if (id >= 0x90) {
                    if (id < 0xa6 || id == 0xca) {
                        page = 0;
                    } else if (id < 0xd0) {
                        page = 2;
                    }
                }
                break;
            case 1:
            case 2:
                if (id < 0x90) {
                    page = 1;
                }
                break;
            case 3:
                if (id >= 0xd0 && id < 0x110) {
                    page = 4;
                }
                break;
            case 4:
                if (id >= 0x120 && id < 0x160) {
                    page = 2;
                }
                break;
            }
            if (page != 5) {
                SetStatusPageAndCursor_020c2ca4(page, -1);
            }
        }

        if ((repeat & 0xf0) || (pressed & 0x300)) {
            UpdateItemDescription_020cd384(panel);
            if (changed) {
                SetupScrollList_020bdf10(&panel->list, panel->container, TRUE);
            } else {
                RefreshScrollListLayout_020be138(&panel->list, panel->container);
            }
            refresh = TRUE;
        }
        if (!changed) {
            if (scrolled) {
                func_ov075_020cdf88(panel);
            }
            if (refresh) {
                SyncCursorElement(panel);
            }
        } else {
            SyncCursorElement(panel);
            func_ov075_020cdf88(panel);
        }
        panel->busy = 0;
    }
    return 1;
}
