#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct TrackState {
    u8 id;
    u8 pad_01[3];
    VecFx32 position;
    s16 scale;
    u16 angle;
    s32 rate;
    u8 pad_18[0xd];
    u8 loop;
    u8 pad_26[2];
    s16 prevIndex;
    s16 index;
} TrackState;

typedef struct EffectResources {
    u8 pad_00[0xb6];
    s16 trailGroup;
} EffectResources;

typedef struct EffectOwner {
    u8 pad_00[0x10];
    s32 effectSlot;
} EffectOwner;

extern EffectResources *data_ov001_020a049c;

extern void func_ov021_020a8ab4(TrackState *state);
extern void VEC_MultAdd_01ffa09c(int scale, const VecFx32 *v, const VecFx32 *add, VecFx32 *dst);
extern u16 FixedPointAtan2_020062bc(fx32 y, fx32 x);
extern int func_ov021_020a8ca0(TrackState *request, int groupId);

void SpawnTrailEffect_0206d050(EffectOwner *owner, const VecFx32 *origin, const VecFx32 *direction)
{
    EffectResources *resources = data_ov001_020a049c;
    TrackState request;

    if (owner->effectSlot < 0) {
        func_ov021_020a8ab4(&request);
        request.id = 0;
        request.loop = 0;
        VEC_MultAdd_01ffa09c(-0x800, direction, origin, &request.position);
        request.angle = FixedPointAtan2_020062bc(direction->x, direction->z);
        request.scale = 0x2000;
        owner->effectSlot = func_ov021_020a8ca0(&request, resources->trailGroup);
    }
}
