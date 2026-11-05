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

extern void UpdateDisplayObjectListQueued(NNSFndList *list);

void InitStateLists(Ov101State *state)
{
    UpdateDisplayObjectListQueued(&state->firstList);
    UpdateDisplayObjectListQueued(&state->secondList);
}
