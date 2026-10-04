#include "nitro/types.h"

typedef struct {
    s32 selectedItem;
    u8 pad_0004[0xCE60 - 0x4];
    s32 pages[40];
    s32 pageCounts[40];
} Ov101State;

extern u16 data_02060500;
extern BOOL IsStateFlagSet_020c07a8(int setIndex, int bitIndex);
extern u32 func_ov101_020c0c3c(void);
extern void SetStatePhase_020c0c18(s32 phase);
extern BOOL PlaySoundEffect_0204d924(int seqArcNo, int index);

void NextItemPage_020bee80(Ov101State *state)
{
    int item = state->selectedItem;
    int count;

    if (!IsStateFlagSet_020c07a8(0, item)) {
        return;
    }
    if (!(data_02060500 & 0x10) && !(data_02060500 & 1)) {
        return;
    }
    if (func_ov101_020c0c3c() == 1) {
        return;
    }
    count = state->pageCounts[item];
    if (count == 1) {
        return;
    }
    state->pages[item]++;
    if (state->pages[item] > count - 1) {
        state->pages[item] = 0;
    }
    SetStatePhase_020c0c18(1);
    PlaySoundEffect_0204d924(0, 1);
}
