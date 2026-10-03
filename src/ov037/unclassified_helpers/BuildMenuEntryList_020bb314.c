#include "nitro/types.h"

typedef struct Ov037Context {
    s16 state;
    u16 entryCount;
    s32 freeSlots;
} Ov037Context;

typedef struct FieldState {
    u8 pad_000[0x214];
    u32 lowFlags : 11;
    u32 restrictedMenu : 1;
} FieldState;

extern Ov037Context *g_ov037Context_020bb764;
extern FieldState *data_ov001_020a0460;
extern s32 data_0205fe20;
extern void func_ov037_020bb2e0(u32 slot, u32 entry);
extern u32 ReadSessionPackedBits_02064574(int bitOffset, u32 bitCount);

void BuildMenuEntryList_020bb314(void)
{
    g_ov037Context_020bb764->entryCount = 0;
    if (data_ov001_020a0460->restrictedMenu) {
        func_ov037_020bb2e0(0, 0x19);
    } else {
        func_ov037_020bb2e0(0, 0);
        if (data_0205fe20 != 0) {
            func_ov037_020bb2e0(1, 1);
        }
        func_ov037_020bb2e0(2, 2);
        if (ReadSessionPackedBits_02064574(0x1a00, 2) == 3) {
            func_ov037_020bb2e0(3, 3);
        }
    }
    g_ov037Context_020bb764->freeSlots = 0x12 - g_ov037Context_020bb764->entryCount;
}
