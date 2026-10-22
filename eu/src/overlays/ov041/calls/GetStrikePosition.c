#include "nitro/types.h"
#include "nitro/fx.h"
#include "src/overlays/ov041/StageEntryRender.h"

extern const VecFx32 data_ov041_020cf7bc[];
extern fx32 FX_Div(fx32 numer, fx32 denom);
extern fx32 FX_Mul(fx32 a, fx32 b);
extern void GetPositionAboveGround(VecFx32 *position, StageEntry *entry);
extern void VEC_Subtract(const VecFx32 *a, const VecFx32 *b, VecFx32 *out);
extern void VEC_Add(const VecFx32 *a, const VecFx32 *b, VecFx32 *out);
extern fx32 VEC_Mag(const VecFx32 *v);
extern fx32 VEC_NormalizeLength(const VecFx32 *source, VecFx32 *dest);
extern void ScaleVecFx32(fx32 scale, const VecFx32 *source, VecFx32 *dest);

/*
 * Where an attacker stops to strike a target: 70% of the way from the attacker to the near edge of the target
 * (its radius on the attacker's side), both lifted by the current height row; a player never passes x = 0 and
 * kind 0x12 stands one unit higher. The action is passed along but not looked at.
 */
void GetStrikePosition(VecFx32 *out, StageEntry *attacker, StageEntry *target, StageEntryAction *action)
{
    StageWork *work = gMovieContextState->stageWork;
    fx32 radius;
    VecFx32 step;
    VecFx32 to;
    VecFx32 from;
    fx32 distance;

    if (attacker->flags & STAGE_ENTRY_ENEMY) {
        radius = FX_Div(target->radius, -FX32_ONE);
    } else {
        radius = target->radius;
    }
    GetPositionAboveGround(&to, target);
    to.x += radius;
    GetPositionAboveGround(&from, attacker);
    from.z -= data_ov041_020cf7bc[work->shadowHeightIndex].x + 0x4000;
    to.z -= data_ov041_020cf7bc[work->shadowHeightIndex].x + 0x4000;
    VEC_Subtract(&to, &from, &step);
    distance = VEC_Mag(&step);
    VEC_NormalizeLength(&step, &step);
    ScaleVecFx32(FX_Mul(distance, 0xb33), &step, &step);
    VEC_Add(&from, &step, &step);
    if (!(attacker->flags & STAGE_ENTRY_ENEMY) && step.x > 0.0f) {
        step.x = 0;
    }
    if (attacker->kind == 0x12) {
        step.y += FX32_ONE;
    }
    *out = step;
}
