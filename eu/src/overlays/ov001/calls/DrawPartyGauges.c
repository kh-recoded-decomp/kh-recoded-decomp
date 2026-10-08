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

extern BOOL IsModeSetOrFlag370aClear(void);
extern void ApplyDefaultSceneCamera(void);
extern BOOL IsHudFlag7Set(void);
extern BOOL IsFieldFlag10Set(void);
extern BOOL IsFieldFlag8Set(void);
extern BOOL IsHudFlag9Set(void);
extern GaugeEntry *CycleMenuEntry(FieldMenu *menu, s32 group, s32 slot, s32 *outIndex);
extern void GetGaugeRect(FieldMenu *menu, GaugeEntry *entry, s32 index, u32 value, u16 *outLeft,
                                  u16 *outRight, u16 *outTop, u16 *outBottom, u16 *outFill);
extern void DrawGradientRect(u32 x0, u32 y0, u32 x1, u32 y1, u32 mode, u32 color, u32 shade);

void DrawPartyGauges(FieldMenu *menu)
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

    if (menu->unk_118 != 0 && IsModeSetOrFlag370aClear()) {
        ApplyDefaultSceneCamera();
        if (IsHudFlag7Set() || IsFieldFlag10Set()) {
            if (menu->unk_C8 <= 0) {
                return;
            }
            entry = CycleMenuEntry(menu, menu->unk_EC, 1, NULL);
            GetGaugeRect(menu, entry, 1, entry->count, &left, &right, &top, &bottom, &fill);
            left += 8;
            right += 8;
            fill += 8;
            DrawGradientRect(left, top, fill, bottom, 0x2000, 0x3161, 0x7B01);
            DrawGradientRect(fill, top, right, bottom, 0x2000, 0x2529, 0x2529);
            return;
        }
        for (index = -1; index < 2; index++) {
            entry = CycleMenuEntry(menu, (menu->state == 2 || menu->state == 3) ? menu->unk_F0 : menu->unk_EC,
                                        index + 1, &entryIndex);
            if ((menu->unk_C8 == 2 && index == -1) || (menu->unk_C8 == 1 && index != 0) || entry->unk_0C == -1 ||
                entry->kind == 3 || (entry->kind == 5 && entry->count == 0)) {
                value = 0xFFFF;
            } else if (IsFieldFlag8Set()) {
                if (entry->flags & 0x10) {
                    value = entry->current;
                    if (value >= entry->limit) {
                        value = entry->limit;
                        if (IsHudFlag9Set()) {
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
            GetGaugeRect(menu, entry, index, value, &left, &right, &top, &bottom, &fill);
            if ((entry->flags & 1) || value == 0xFFFF) {
                DrawGradientRect(left, top, right, bottom, 0x2000, 0, 0);
            } else {
                if (fill > left) {
                    DrawGradientRect(left, top, fill, bottom, 0x2000, 0x3161, 0x7B01);
                }
                if (value < entry->limit) {
                    DrawGradientRect(fill, top, right, bottom, 0x2000, 0x2529, 0x2529);
                }
            }
        }
    }
}
