#include "nitro/types.h"

typedef struct {
    u8 pad[0x3f08];
    int pendingSlots[5];
} SlotState;

extern SlotState *data_ov001_020a04e0;
extern void ActorSlot_SetFlag8ByIndex_02036120(int index, BOOL enable);

void QueueActorSlotRelease_02088a44(int slot) {
    int i;
    for (i = 0; i < 5; i++) {
        if (data_ov001_020a04e0->pendingSlots[i] == -1) {
            data_ov001_020a04e0->pendingSlots[i] = slot;
            break;
        }
    }
    ActorSlot_SetFlag8ByIndex_02036120((u16)slot, FALSE);
}
