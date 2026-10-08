#include "nitro/types.h"

typedef struct {
    void *headObject;
    void *tailObject;
    u16 numObjects;
    u16 offset;
} NNSFndList;

typedef struct {
    u8 pad_0000[0x184];
    NNSFndList firstList;
    u8 pad_0190[0x65B8 - 0x190];
    NNSFndList secondList;
} Ov101State;

extern void NNS_FndInitListWithOffset0_0204f130(NNSFndList *list);

void InitStateLists(Ov101State *state)
{
    NNS_FndInitListWithOffset0_0204f130(&state->firstList);
    NNS_FndInitListWithOffset0_0204f130(&state->secondList);
}
