#include "nitro/types.h"

typedef union TouchPos {
    u32 raw;
    struct {
        s16 x;
        s16 y;
    };
} TouchPos;

typedef struct TouchState {
    u8 pad_00[4];
    TouchPos pos;
    u16 state;
} TouchState;

typedef struct PanelRect {
    u8 width;
    u8 height;
    s8 marginX;
    s8 marginY;
} PanelRect;

typedef struct ScaleTable {
    u8 values[6];
} ScaleTable;

typedef struct SlotMenu {
    u8 pad_00000[0x12dc0];
    TouchState *touch;
    u8 pad_12dc4[0x13e88 - 0x12dc4];
    BOOL dragging;
    u8 pad_13e8c[0x13ebc - 0x13e8c];
    TouchPos cursor;
    int scale;
} SlotMenu;

extern PanelRect data_ov075_020d1480;
extern ScaleTable data_ov075_020d14a8;
extern u16 data_02060500;

extern int FX_Sqrt_01ff9cfc(int value);
extern BOOL PlaySoundEffect_0204d924(int seqArcNo, int index);
extern u8 EncodeTouchSlot_020c48e8(TouchPos pos, int direction);
extern TouchPos GetSlotCellOffset_020c493c(int code);

static inline u16 AbsS16(s16 value)
{
    s16 sign = value >> 15;

    return (value ^ sign) - sign;
}

BOOL UpdateSlotCursor_020cc5a8(SlotMenu *menu, u8 *code, BOOL changed)
{
    TouchPos local;
    ScaleTable table;
    TouchPos pos;
    BOOL tappedOutside = FALSE;
    BOOL outside;
    u8 previous;
    BOOL snap = FALSE;

    previous = *code;

    if (!changed) {
        TouchState *touch = menu->touch;
        u8 state = touch->state & 3;

        if (state != 0) {
            PanelRect *rect;

            pos = touch->pos;
            outside = TRUE;
            rect = &data_ov075_020d1480;
            if (AbsS16(pos.x - 0x80) < (rect->width >> 1) + rect->marginX
                && AbsS16(pos.y - 0x60) < (rect->height >> 1) + rect->marginY) {
                outside = FALSE;
            }
            if (state == 1) {
                if (outside) {
                    tappedOutside = TRUE;
                } else {
                    int dx = touch->pos.x - (menu->cursor.x + 0x50);
                    int dy = touch->pos.y - (menu->cursor.y + 0x61);

                    if (FX_Sqrt_01ff9cfc((dx * dx + dy * dy) << 12) <= 0x7000) {
                        menu->dragging = TRUE;
                    }
                }
            }
            if (menu->dragging && state != 2) {
                u16 offset;
                s16 distX;
                s16 x = menu->cursor.x;
                s16 distY;
                s16 y;

                offset = x % 16;
                local.raw = menu->touch->pos.raw;
                local.x -= 0x50;
                local.y -= 0x61;
                distX = AbsS16(local.x - x);
                y = menu->cursor.y;
                distY = AbsS16(local.y - y);
                if (y == 0 && (distY < distX || offset != 0)) {
                    if (distX >= 8) {
                        menu->cursor.x += (s16)(local.x < x ? -8 : 8);
                    } else {
                        menu->cursor.x = local.x;
                    }
                    if (menu->cursor.x < 0) {
                        menu->cursor.x = 0;
                    } else if (menu->cursor.x > 0x30) {
                        menu->cursor.x = 0x30;
                    }
                } else if (offset == 0 && distY > 0) {
                    if (distY >= 8) {
                        menu->cursor.y += (s16)(local.y < y ? -8 : 8);
                    } else {
                        menu->cursor.y = local.y;
                    }
                    if (menu->cursor.y < -18) {
                        menu->cursor.y = -18;
                    } else if (menu->cursor.y > 18) {
                        menu->cursor.y = 18;
                    }
                    if ((menu->cursor.y < 0 && menu->cursor.x == 0x30) || (menu->cursor.y > 0 && menu->cursor.x == 0)) {
                        menu->cursor.y = 0;
                    }
                }
                changed = TRUE;
            } else {
                snap = FALSE;
                menu->dragging = FALSE;
                if (state == 2) {
                    snap = TRUE;
                }
            }
        } else {
            u16 keys = data_02060500;
            int top = previous >> 7;
            u16 slot = previous & 7;
            u16 row = (previous >> 3) & 3;

            if ((keys & 0x40) && ((top && row != 3) || (!top && slot >= 3))) {
                menu->cursor.y -= 18;
                changed = TRUE;
                snap = TRUE;
            } else if ((keys & 0x80) && ((top && row != 0) || (!top && slot < 3))) {
                menu->cursor.y += 18;
                changed = TRUE;
                snap = TRUE;
            } else if ((keys & 0x20) && top && row != 0) {
                menu->cursor.x -= 16;
                changed = TRUE;
                snap = TRUE;
            } else if ((keys & 0x10) && top && row < 3) {
                menu->cursor.x += 16;
                changed = TRUE;
                snap = TRUE;
            }
            menu->dragging = FALSE;
        }
    } else {
        menu->cursor = GetSlotCellOffset_020c493c(previous);
    }
    if (changed) {
        *code = EncodeTouchSlot_020c48e8(menu->cursor, *code);
    }
    if (changed || snap) {
        u8 current = *code;

        if (snap) {
            menu->cursor = GetSlotCellOffset_020c493c(current);
        }
        if (!(current >> 7)) {
            table = data_ov075_020d14a8;
            menu->scale = table.values[current & 7] << 12;
        }
    }
    if (previous != *code) {
        PlaySoundEffect_0204d924(1, 10);
    }
    return tappedOutside;
}
