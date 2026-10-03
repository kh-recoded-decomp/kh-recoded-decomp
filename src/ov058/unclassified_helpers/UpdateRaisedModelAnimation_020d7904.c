#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct {
    u8 pad_000[0xa4];
    VecFx32 offset;
    u8 pad_0b0[0x130 - 0xb0];
    s32 phase;
} EmitterRig;

extern const VecFx32 data_ov058_020d8a2c;

extern BOOL AdvanceAnimationTracks_0202ef24(EmitterRig *rig, fx32 step);

void UpdateRaisedModelAnimation_020d7904(EmitterRig *rig, fx32 step)
{
    VecFx32 offset;

    if (rig->phase == 0) {
        return;
    }
    offset = data_ov058_020d8a2c;
    offset.y += 0x2000;
    rig->offset = offset;
    if (rig->phase == 1 && AdvanceAnimationTracks_0202ef24(rig, step)) {
        rig->phase = 0;
    }
}
