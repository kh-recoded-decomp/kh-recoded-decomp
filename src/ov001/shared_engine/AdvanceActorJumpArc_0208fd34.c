#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct JumpArc {
    VecFx32 origin;
    VecFx32 velocity;
    fx32 unk_18;
    fx32 gravity;
} JumpArc;

typedef struct JumpActor {
    u8 pad_000[0x29c];
    fx32 moveSpeed;
    u8 pad_2a0[0x9c];
    JumpArc arc;
    u8 pad_35c[0x4];
    fx32 arcTime;
    fx32 arcDuration;
} JumpActor;

extern void EvaluateJumpArc_0209d554(JumpArc *arc, fx32 time, VecFx32 *out);
extern fx32 ApplyActorScaleFactors_02091818(JumpActor *actor);
extern void VEC_Subtract_01ff9e3c(const VecFx32 *a, const VecFx32 *b, VecFx32 *out);
extern void VEC_Add_01ff9e0c(const VecFx32 *a, const VecFx32 *b, VecFx32 *out);

void AdvanceActorJumpArc_0208fd34(JumpActor *actor, VecFx32 *position)
{
    VecFx32 prevPoint;
    VecFx32 nextPoint;
    VecFx32 delta;

    if (actor->arcDuration != 0) {
        actor->moveSpeed = 0;
        EvaluateJumpArc_0209d554(&actor->arc, actor->arcTime, &prevPoint);
        actor->arcTime += ApplyActorScaleFactors_02091818(actor);
        EvaluateJumpArc_0209d554(&actor->arc, actor->arcTime, &nextPoint);
        VEC_Subtract_01ff9e3c(&nextPoint, &prevPoint, &delta);
        VEC_Add_01ff9e0c(position, &delta, position);
        if (actor->arcTime >= actor->arcDuration) {
            actor->arcTime = 0;
            actor->arcDuration = 0;
        }
    }
}
