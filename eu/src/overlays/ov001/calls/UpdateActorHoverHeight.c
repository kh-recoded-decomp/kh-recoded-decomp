#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct HoverActor {
    u8 pad_000[0x28a];
    u16 unk_28A_0 : 15;
    u16 bobbing : 1;
    u16 unk_28C_0 : 11;
    u16 floorLayer : 3;
    u16 unk_28C_14 : 2;
    u8 pad_28e[0x1a];
    fx32 climbSpeed;
    u8 pad_2ac[0x14];
    VecFx32 position;
    VecFx32 targetPosition;
    u8 pad_2d8[0x5c];
    fx32 hoverHeight;
    u16 bobPhase;
    u8 pad_33a[0x62];
    fx32 speedScale;
} HoverActor;

extern const s16 data_02053580[];
extern u32 GetGlobalScaleValue(void);
extern fx32 FX_Mul(fx32 a, fx32 b);
extern void FindNearestStageEntry(VecFx32 *position);
extern void SyncStageEntryPosition(u16 layer, VecFx32 *out);
extern fx32 FX_Div(fx32 numer, fx32 denom);

void UpdateActorHoverHeight(HoverActor *actor, VecFx32 *position)
{
    fx32 bobOffset;
    VecFx32 target;
    VecFx32 layerOffset;
    fx32 maxStep;
    fx32 difference;
    long distance;

    if (actor->hoverHeight != 0) {
        target = actor->targetPosition;
        maxStep = FX_Mul(actor->climbSpeed, FX_Mul(GetGlobalScaleValue(), actor->speedScale));
        FindNearestStageEntry(&actor->position);
        SyncStageEntryPosition(actor->floorLayer, &layerOffset);
        if (actor->bobbing) {
            actor->bobPhase += 0x100;
            bobOffset = FX_Mul(data_02053580[actor->bobPhase >> 4], 0x333);
        }
        target.y = bobOffset + (layerOffset.y + actor->hoverHeight);
        difference = target.y - actor->position.y;
        distance = difference;
        if ((distance < 0 ? -distance : distance) < maxStep) {
            position->y = target.y;
        } else {
            if (distance < 0) {
                distance = -distance;
            }
            position->y += FX_Mul(FX_Div(difference, distance), maxStep);
        }
    }
}
