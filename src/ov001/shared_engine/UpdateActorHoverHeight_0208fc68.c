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

extern const s16 data_0205356c[];
extern u32 GetGlobalScaleValue_0209c3cc(void);
extern fx32 FixedPointMultiply12(fx32 a, fx32 b);
extern void func_ov001_02099328(VecFx32 *position);
extern void GetStageLayerOffset_02098fbc(u16 layer, VecFx32 *out);
extern fx32 FX_Div_01ff9c84(fx32 numer, fx32 denom);

void UpdateActorHoverHeight_0208fc68(HoverActor *actor, VecFx32 *position)
{
    fx32 bobOffset;
    VecFx32 target;
    VecFx32 layerOffset;
    fx32 maxStep;
    fx32 difference;
    int distance;

    if (actor->hoverHeight != 0) {
        target = actor->targetPosition;
        maxStep = FixedPointMultiply12(actor->climbSpeed, FixedPointMultiply12(GetGlobalScaleValue_0209c3cc(), actor->speedScale));
        func_ov001_02099328(&actor->position);
        GetStageLayerOffset_02098fbc(actor->floorLayer, &layerOffset);
        if (actor->bobbing) {
            actor->bobPhase += 0x100;
            bobOffset = FixedPointMultiply12(data_0205356c[actor->bobPhase >> 4], 0x333);
        }
        target.y = bobOffset + (layerOffset.y + actor->hoverHeight);
        difference = target.y - actor->position.y;
        distance = difference;
        if ((difference < 0 ? -difference : difference) < maxStep) {
            position->y = target.y;
        } else {
            if (distance < 0) {
                distance = -distance;
            }
            position->y += FixedPointMultiply12(FX_Div_01ff9c84(difference, distance), maxStep);
        }
    }
}
