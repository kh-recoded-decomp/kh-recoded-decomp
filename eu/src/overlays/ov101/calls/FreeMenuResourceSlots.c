#include "nitro/types.h"

typedef struct {
    void *data;
    u8 pad_04[0xC];
} ResourceSlot;

typedef struct {
    u8 pad_000[0x154];
    ResourceSlot slots[3];
} Ov101State;

extern void NNSi_FndFreeFromDefaultHeap(void *block);

void FreeMenuResourceSlots(Ov101State *state)
{
    int i;

    for (i = 0; i < 3; i++) {
        if (state->slots[i].data != NULL) {
            NNSi_FndFreeFromDefaultHeap(state->slots[i].data);
        }
    }
}
