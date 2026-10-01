#include "nitro/types.h"

typedef struct {
    u8 pad_00[0x40];
    const u16 *name;
    u8 pad_44[4];
} RecordEntry;

typedef struct {
    u8 pad_000[0xc];
    u8 textLayer[0x160];
    BOOL firstGoalReached;
    BOOL secondGoalReached;
} Ov086Menu;

extern void *func_ov027_020ba2a8(Ov086Menu *menu, int messageId);
extern void DrawTextAnchored_020015a0(void *layer, int x, int y, int color, u32 flags, const void *text);
extern int func_ov001_02064574(int bitIndex, int bitCount);
extern void *OS_SNPrintf_0202e080(char *dst, unsigned int len, const char *fmt, ...);
extern RecordEntry *GetRecordSlotPair0Entry_02051ec8(s32 index);
extern const u16 data_ov086_020c2fc4[];
extern const char data_ov086_020c2fc8[];

void DrawSecondCounterText_020bfd0c(Ov086Menu *menu)
{
    char buffer[0x20];
    int value;
    const u16 *name;
    int color;

    DrawTextAnchored_020015a0(menu->textLayer, 0x38, 0x12, 6, 0x209, func_ov027_020ba2a8(menu, 0x16));
    DrawTextAnchored_020015a0(menu->textLayer, 0x6f, 0x12, 4, 0x209, data_ov086_020c2fc4);
    value = func_ov001_02064574(0xe3e, 0x14);
    OS_SNPrintf_0202e080(buffer, 0x10, data_ov086_020c2fc8, value);
    DrawTextAnchored_020015a0(menu->textLayer, 0xa0, 0x12, 2, 0x821, buffer);
    color = 2;
    name = GetRecordSlotPair0Entry_02051ec8(0xf3)->name;
    DrawTextAnchored_020015a0(menu->textLayer, 0x27, 0x33, 1, 0x209, name);
    if (value < 1) {
        color = 4;
    }
    DrawTextAnchored_020015a0(menu->textLayer, 0x26, 0x32, color, 0x209, name);
    if (value >= 1) {
        menu->secondGoalReached = TRUE;
    }
}
