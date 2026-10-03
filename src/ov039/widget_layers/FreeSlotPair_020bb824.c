#include "nitro/types.h"

typedef struct {
    u8 pad_0000[0xcab4];
    void *slots[4];
} Ov039State;

extern int ZeroHalfThenFree_0202cd78(void *block);

void FreeSlotPair_020bb824(Ov039State *state, int slot)
{
    if (state->slots[slot] != 0) {
        ZeroHalfThenFree_0202cd78(state->slots[slot]);
        state->slots[slot] = 0;
    }
    slot++;
    if (state->slots[slot] != 0) {
        ZeroHalfThenFree_0202cd78(state->slots[slot]);
        state->slots[slot] = 0;
    }
}
