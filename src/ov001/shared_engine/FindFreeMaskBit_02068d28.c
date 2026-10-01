#include "nitro/types.h"

typedef struct MaskState {
    u8 pad_00[0x20];
    u16 usedMask;
} MaskState;

extern MaskState *data_ov001_020a0474;

int FindFreeMaskBit_02068d28(int start, int count)
{
    MaskState *state = data_ov001_020a0474;
    int i;
    int result = -1;

    for (i = 0; i < count; i++) {
        int bit = start + i;

        if (!((1 << bit) & state->usedMask)) {
            result = bit;
            break;
        }
    }
    return result;
}
