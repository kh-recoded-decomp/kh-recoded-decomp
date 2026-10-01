#include "nitro/types.h"
#include "nitro/hw.h"

typedef struct TouchState {
    u8 pad_00[4];
    s16 x;
    s16 y;
    u16 state;
    u16 buttons;
} TouchState;

typedef struct ScrollList {
    s16 itemCount;
    s16 cursor;
    s16 topIndex;
    u8 scrollOffset;
    u8 visibleRows;
    u8 pad_08[0x14 - 0x08];
    BOOL inputLocked;
    u8 pad_18[0xd4 - 0x18];
} ScrollList;

typedef struct StatusMenu {
    u8 unk_00;
    u8 dirty;
    u8 pad_02[0x10 - 0x02];
    s16 lastCursor;
    u8 pad_12[0x10e0 - 0x12];
    void *container;
    u8 pad_10e4[0x10f4 - 0x10e4];
    ScrollList list;
    s16 dragIndex;
    s16 dragTarget;
} StatusMenu;

typedef struct SlotEntry {
    void *data;
    u8 pad_04[0xc];
} SlotEntry;

typedef struct SlotSummary {
    u8 unk_00;
    u8 heldIndex;
    u8 unk_02;
    u8 isHolding;
    SlotEntry slots[8];
    u32 savedSlot;
} SlotSummary;

typedef struct SaveData {
    u8 pad_0000[0x28d7];
    u8 currentSlot : 4;
    u8 unk_28d7 : 4;
} SaveData;

extern SaveData *data_0205fe0c;
extern u16 g_padTrigger_02060500;

extern TouchState *func_ov039_020bca00(void);
extern int func_ov039_020bd624(void);
extern int func_ov039_020be0c4(ScrollList *list, void *owner);
extern BOOL func_ov076_020c8f24(void);
extern BOOL PlaySoundEffect_0204d924(int seqArcNo, int index);
extern void SetStatusElementVisible_020beb5c(int elementId, BOOL visible);
extern void func_ov073_020bebd0(SlotSummary *summary, int fromIndex, int toIndex);
extern void func_ov073_020c026c(StatusMenu *menu, SlotSummary *summary);
extern void func_ov073_020c02d4(SlotSummary *summary, int slotIndex);

static inline int UpdateStatusList(StatusMenu *menu)
{
    int scroll;

    if (menu->list.itemCount <= 1) {
        return -1;
    }
    scroll = func_ov039_020be0c4(&menu->list, menu->container);
    if (menu->lastCursor != menu->list.cursor && (func_ov039_020bca00()->state & 3) == 1) {
        scroll = 2;
    }
    menu->lastCursor = menu->list.cursor;
    return scroll;
}

BOOL HandleSlotListInput_020c032c(StatusMenu *menu, SlotSummary *summary)
{
    BOOL canConfirm = TRUE;
    BOOL result = FALSE;
    TouchState *touch;
    int scroll;
    int row;
    int limit;
    s16 x;
    s16 y;

    if ((*(vu16 *)REG_POWCNT_ADDR & 0x8000) >> 15 == 1) {
        touch = func_ov039_020bca00();
    } else {
        touch = NULL;
    }

    if (touch != NULL && (touch->state & 3) != 0 && !summary->isHolding) {
        menu->dirty |= (u8)(UpdateStatusList(menu) != 0);
        switch (touch->state & 3) {
        case 1:
            if (menu->dragIndex >= 0) {
                break;
            }
            x = touch->x;
            if (x < 0x30 || x >= 0xd8) {
                break;
            }
            y = touch->y;
            if (y < 0x18 || y >= 0x84) {
                break;
            }
            row = menu->list.topIndex + ((y - 0x18) >> 4);
            if (row >= menu->list.itemCount) {
                break;
            }
            if (x > 0x40) {
                if (menu->list.cursor != row) {
                    PlaySoundEffect_0204d924(0, 0);
                }
                menu->list.cursor = row;
                menu->dragTarget = menu->list.cursor;
                menu->dragIndex = menu->dragTarget;
                summary->savedSlot = data_0205fe0c->currentSlot;
                menu->list.inputLocked = TRUE;
            } else if (row != data_0205fe0c->currentSlot) {
                if (summary->slots[row].data != NULL) {
                    func_ov073_020c02d4(summary, row);
                    PlaySoundEffect_0204d924(0, 1);
                } else {
                    PlaySoundEffect_0204d924(0, 4);
                }
                PlaySoundEffect_0204d924(0, 1);
            }
            menu->dirty = TRUE;
            break;
        case 3:
            if (menu->dragIndex < 0) {
                break;
            }
            x = touch->x;
            if (x >= 0x30 && x < 0xd8) {
                row = menu->list.topIndex + ((touch->y - 0x18) >> 4);
                if (row < menu->list.topIndex) {
                    row = menu->list.topIndex;
                } else {
                    limit = (menu->list.visibleRows < menu->list.itemCount) ? menu->list.visibleRows : menu->list.itemCount;
                    limit += menu->list.topIndex;
                    if (row >= limit) {
                        row = limit - 1;
                    }
                }
                menu->list.cursor = row;
                if (menu->dragTarget == row) {
                    break;
                }
                func_ov073_020bebd0(summary, menu->dragTarget, row);
                func_ov073_020c026c(menu, summary);
                menu->dirty = TRUE;
                menu->dragTarget = row;
                break;
            }
            PlaySoundEffect_0204d924(0, 3);
            func_ov073_020bebd0(summary, menu->dragTarget, menu->dragIndex);
            data_0205fe0c->currentSlot = summary->savedSlot;
            menu->dragIndex = -1;
            menu->dirty = TRUE;
            break;
        case 2:
            if (menu->dragIndex >= 0) {
                menu->dragIndex = -1;
                if (menu->dragIndex != menu->dragTarget) {
                    PlaySoundEffect_0204d924(0, 1);
                }
            }
            menu->list.inputLocked = FALSE;
            break;
        }
    } else {
        scroll = UpdateStatusList(menu);
        if (scroll != 0 || (func_ov039_020bca00()->buttons & 0xf0) != 0) {
            menu->dirty = TRUE;
        }
        if (func_ov039_020bd624() == 2 && func_ov076_020c8f24()) {
            canConfirm = FALSE;
        }
        if (g_padTrigger_02060500 & 0x800) {
            if (data_0205fe0c->currentSlot != menu->list.cursor) {
                if (summary->slots[menu->list.cursor].data != NULL) {
                    func_ov073_020c02d4(summary, menu->list.cursor);
                    menu->dirty = TRUE;
                    PlaySoundEffect_0204d924(0, 1);
                } else {
                    PlaySoundEffect_0204d924(0, 4);
                }
            }
            result = TRUE;
        } else if (g_padTrigger_02060500 & 1) {
            if (canConfirm) {
                if (summary->isHolding) {
                    func_ov073_020bebd0(summary, summary->heldIndex, menu->list.cursor);
                    func_ov073_020c026c(menu, summary);
                    summary->isHolding = FALSE;
                    SetStatusElementVisible_020beb5c(3, TRUE);
                } else {
                    summary->isHolding = TRUE;
                    SetStatusElementVisible_020beb5c(3, FALSE);
                    summary->heldIndex = menu->list.cursor;
                }
                menu->dirty = TRUE;
                PlaySoundEffect_0204d924(0, 1);
            } else {
                PlaySoundEffect_0204d924(0, 4);
            }
            result = TRUE;
        } else if (g_padTrigger_02060500 & 0x402) {
            if (summary->isHolding) {
                summary->isHolding = FALSE;
                SetStatusElementVisible_020beb5c(3, TRUE);
                result = TRUE;
                menu->dirty = TRUE;
                if (g_padTrigger_02060500 & 0x400) {
                    result = FALSE;
                }
                if (result) {
                    PlaySoundEffect_0204d924(0, 3);
                }
            }
        } else if (g_padTrigger_02060500 & 0x300) {
            if (summary->isHolding) {
                return TRUE;
            }
        }
    }
    return result;
}
