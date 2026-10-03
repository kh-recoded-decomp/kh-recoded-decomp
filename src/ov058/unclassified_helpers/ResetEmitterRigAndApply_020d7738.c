#include "nitro/types.h"

typedef struct {
    u8 pad_000[0x130];
    s32 phase;
} EmitterRig;

extern void RebindEmitterSlots_020d7498(EmitterRig *rig, int blend);
extern void func_ov058_020d7818(EmitterRig *rig, int arg);

void ResetEmitterRigAndApply_020d7738(EmitterRig *rig, int arg)
{
    rig->phase = 1;
    RebindEmitterSlots_020d7498(rig, 0);
    func_ov058_020d7818(rig, arg);
}
