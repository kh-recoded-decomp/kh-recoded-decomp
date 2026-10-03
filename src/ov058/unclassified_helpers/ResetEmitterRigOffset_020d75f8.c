#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct {
    u8 pad_000[0xa4];
    VecFx32 offset;
    u8 pad_0b0[0x130 - 0xb0];
    s32 phase;
} EmitterRig;

extern const VecFx32 data_ov058_020d8a2c;

extern void RebindEmitterSlots_020d7498(EmitterRig *rig, int blend);

void ResetEmitterRigOffset_020d75f8(EmitterRig *rig)
{
    rig->phase = 1;
    RebindEmitterSlots_020d7498(rig, 0);
    rig->offset = data_ov058_020d8a2c;
}
