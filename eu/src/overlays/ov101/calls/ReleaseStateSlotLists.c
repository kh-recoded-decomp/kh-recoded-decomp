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

extern void Slot_UnlinkAll(void *slots);
extern int Obj_Release(void *object);

void ReleaseStateSlotLists(Ov101State *state)
{
    NNSFndList *list = &state->secondList;
    Slot_UnlinkAll(list);
    Obj_Release(list);
    Slot_UnlinkAll(&state->firstList);
    Obj_Release(&state->firstList);
}
