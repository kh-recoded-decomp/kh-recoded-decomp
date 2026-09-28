#include "nitro/types.h"
#include "nnsys/fnd.h"

typedef struct {
    u8 pad_0000[0x17C];
    NNSFndList firstList;
    u8 pad_0188[0x65B0 - 0x188];
    NNSFndList secondList;
} Ov101State;

extern void NNS_FndInitListWithOffset0_0204f11c(NNSFndList *list);

void InitStateLists_020bfa4c(Ov101State *state)
{
    NNS_FndInitListWithOffset0_0204f11c(&state->firstList);
    NNS_FndInitListWithOffset0_0204f11c(&state->secondList);
}
