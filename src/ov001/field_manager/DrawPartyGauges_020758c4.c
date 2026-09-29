#include "nitro/types.h"

typedef struct {
    u32 current;
    u32 limit;
    u8 pad_08[4];
    s32 unk_0C;
    s32 kind;
    u8 pad_14[0x14];
    u16 flags;
    u16 count;
} GaugeEntry;

typedef struct {
    u8 pad_000[0xC8];
    s32 unk_C8;
    u8 pad_0CC[0x20];
    s32 unk_EC;
    s32 unk_F0;
    u8 pad_0F4[8];
    s32 state;
    u8 pad_100[0x18];
    s32 unk_118;
} FieldMenu;

extern BOOL IsModeSetOrFlag370aClear_0207259c(void);
extern void func_ov001_020752a0(void);
extern BOOL IsHudFlag7Set_020725bc(void);
extern BOOL func_ov001_020728c4(void);
extern BOOL func_ov001_020728a4(void);
extern BOOL IsHudFlag9Set_02072884(void);
extern GaugeEntry *func_ov001_02075348(FieldMenu *menu, s32 group, s32 slot, s32 *outIndex);
extern void GetGaugeRect_020756d4(FieldMenu *menu, GaugeEntry *entry, s32 index, u32 value, u16 *outLeft,
                                  u16 *outRight, u16 *outTop, u16 *outBottom, u16 *outFill);
extern void func_ov001_02075604(u32 x0, u32 y0, u32 x1, u32 y1, u32 mode, u32 color, u32 shade);

void DrawPartyGauges_020758c4(FieldMenu *menu)
{
    GaugeEntry *entry;
    s32 index;
    u16 value;
    u16 left;
    u16 right;
    u16 top;
    u16 bottom;
    u16 fill;
    s32 entryIndex;

    if (menu->unk_118 != 0 && IsModeSetOrFlag370aClear_0207259c()) {
        func_ov001_020752a0();
        if (IsHudFlag7Set_020725bc() || func_ov001_020728c4()) {
            if (menu->unk_C8 <= 0) {
                return;
            }
            entry = func_ov001_02075348(menu, menu->unk_EC, 1, NULL);
            GetGaugeRect_020756d4(menu, entry, 1, entry->count, &left, &right, &top, &bottom, &fill);
            left += 8;
            right += 8;
            fill += 8;
            func_ov001_02075604(left, top, fill, bottom, 0x2000, 0x3161, 0x7B01);
            func_ov001_02075604(fill, top, right, bottom, 0x2000, 0x2529, 0x2529);
            return;
        }
        for (index = -1; index < 2; index++) {
            entry = func_ov001_02075348(menu, (menu->state == 2 || menu->state == 3) ? menu->unk_F0 : menu->unk_EC,
                                        index + 1, &entryIndex);
            if ((menu->unk_C8 == 2 && index == -1) || (menu->unk_C8 == 1 && index != 0) || entry->unk_0C == -1 ||
                entry->kind == 3 || (entry->kind == 5 && entry->count == 0)) {
                value = 0xFFFF;
            } else if (func_ov001_020728a4()) {
                if (entry->flags & 0x10) {
                    value = entry->current;
                    if (value >= entry->limit) {
                        value = entry->limit;
                        if (IsHudFlag9Set_02072884()) {
                            entry->flags |= 3;
                        } else {
                            entry->flags &= ~1;
                        }
                    }
                } else {
                    value = 0xFFFF;
                }
            } else {
                value = entry->current;
                if (value >= entry->limit) {
                    value = entry->limit;
                    if (!(entry->flags & 1)) {
                        entry->flags |= 3;
                    }
                }
            }
            GetGaugeRect_020756d4(menu, entry, index, value, &left, &right, &top, &bottom, &fill);
            if ((entry->flags & 1) || value == 0xFFFF) {
                func_ov001_02075604(left, top, right, bottom, 0x2000, 0, 0);
            } else {
                if (fill > left) {
                    func_ov001_02075604(left, top, fill, bottom, 0x2000, 0x3161, 0x7B01);
                }
                if (value < entry->limit) {
                    func_ov001_02075604(fill, top, right, bottom, 0x2000, 0x2529, 0x2529);
                }
            }
        }
    }
}
