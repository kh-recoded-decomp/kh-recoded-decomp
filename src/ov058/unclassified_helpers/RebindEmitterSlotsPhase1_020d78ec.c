#include "nitro/types.h"

typedef struct {
    u8 pad_000[0x130];
    s32 phase;
} EmitterRig;

extern void RebindEmitterSlots_020d7498(EmitterRig *rig, int blend);

void RebindEmitterSlotsPhase1_020d78ec(EmitterRig *rig)
{
    rig->phase = 1;
    RebindEmitterSlots_020d7498(rig, 0);
}
