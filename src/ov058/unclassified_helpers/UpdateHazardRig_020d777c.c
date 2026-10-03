#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct {
    u8 pad_000[0x130];
    s32 phase;
} EmitterRig;

extern void PlaceRigAtPlayerOffset_020d7818(EmitterRig *rig, int index);
extern u16 AdvanceAnimationTracks_0202ef24(EmitterRig *rig, fx32 step);
extern void RebindEmitterSlots_020d7498(EmitterRig *rig, int blend);
extern void PulseHazardHitScans_020d7a44(int index);

void UpdateHazardRig_020d777c(EmitterRig *rig, int index, fx32 step)
{
    s32 phase = rig->phase;

    if (phase == 0) {
        return;
    }
    switch (phase) {
    case 1:
        PlaceRigAtPlayerOffset_020d7818(rig, index);
        if (AdvanceAnimationTracks_0202ef24(rig, step)) {
            RebindEmitterSlots_020d7498(rig, 1);
            rig->phase = 2;
        }
        break;
    case 2:
        PlaceRigAtPlayerOffset_020d7818(rig, index);
        AdvanceAnimationTracks_0202ef24(rig, step);
        PulseHazardHitScans_020d7a44(index);
        break;
    case 3:
        if (AdvanceAnimationTracks_0202ef24(rig, step)) {
            rig->phase = 0;
        }
        break;
    }
}
