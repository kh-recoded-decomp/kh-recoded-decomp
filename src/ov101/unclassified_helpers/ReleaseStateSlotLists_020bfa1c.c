#include "nitro/types.h"
#include "nnsys/fnd.h"

typedef struct {
    u8 pad_0000[0x17C];
    NNSFndList firstList;
    u8 pad_0188[0x65B0 - 0x188];
    NNSFndList secondList;
} Ov101State;

extern void Slot_UnlinkAll_0204f104(void *slots);
extern int Obj_Release_0204eff8(void *object);

void ReleaseStateSlotLists_020bfa1c(Ov101State *state)
{
    NNSFndList *list = &state->secondList;
    Slot_UnlinkAll_0204f104(list);
    Obj_Release_0204eff8(list);
    Slot_UnlinkAll_0204f104(&state->firstList);
    Obj_Release_0204eff8(&state->firstList);
}
