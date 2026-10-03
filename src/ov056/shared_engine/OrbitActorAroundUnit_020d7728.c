#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct {
    fx32 x;
    fx32 y;
    fx32 z;
    fx32 w;
} QuatFx32;

typedef struct {
    u8 pad_00[0xe0];
    QuatFx32 spin;
    fx32 height;
    fx32 accel;
    fx32 minDistanceSq;
} OrbitDef;

typedef struct {
    u8 pad_000[0xd4];
    VecFx32 position;
    u8 pad_0e0[0x150 - 0xe0];
    OrbitDef *def;
} OrbitUnit;

typedef struct {
    OrbitUnit *unit;
    QuatFx32 rotation;
    fx32 speed;
    s32 state;
} OrbitWork;

typedef struct {
    u8 pad_00[0x10];
    s16 actorId;
} OrbitEvent;

typedef struct StageActor StageActor;

extern StageActor *GetStageActor_0209c040(int id);
extern VecFx32 *func_ov001_02090f04(StageActor *actor);
extern void VEC_Add_01ff9e0c(const VecFx32 *a, const VecFx32 *b, VecFx32 *ab);
extern void VEC_Subtract_01ff9e3c(const VecFx32 *a, const VecFx32 *b, VecFx32 *ab);
extern fx32 VEC_DotProduct_01ff9e6c(const VecFx32 *a, const VecFx32 *b);
extern void VEC_Normalize_01ff9f88(const VecFx32 *src, VecFx32 *dst);
extern void VEC_MultAdd_01ffa09c(fx32 scale, const VecFx32 *v, const VecFx32 *add, VecFx32 *dst);
extern void multiplyFixedPointQuaternions_0202f93c(QuatFx32 *dst, QuatFx32 *a, QuatFx32 *b);
extern void func_0202fba8(VecFx32 *in, QuatFx32 *rotation, VecFx32 *out);
extern void ClearActorMotionState_02091194(StageActor *actor);
extern void ClearActorMotionSpeed_020911a8(StageActor *actor);
extern void AddObjectOffsetVector_02091c50(StageActor *actor, VecFx32 *offset);
extern void func_ov001_020958e4(OrbitEvent *event, int status);

BOOL OrbitActorAroundUnit_020d7728(OrbitEvent *event, OrbitWork *work)
{
    OrbitUnit *unit;
    OrbitDef *def;
    StageActor *actor;
    VecFx32 pos;
    VecFx32 dir;
    VecFx32 center;

    switch (work->state) {
    default:
        work->state = 0;
    case 0:
        func_ov001_020958e4(event, 9);
        break;
    case 1:
        unit = work->unit;
        def = unit->def;
        actor = GetStageActor_0209c040(event->actorId);
        center = unit->position;
        pos = *func_ov001_02090f04(actor);
        VEC_Subtract_01ff9e3c(&pos, &center, &dir);
        multiplyFixedPointQuaternions_0202f93c(&work->rotation, &work->rotation, &def->spin);
        func_0202fba8(&dir, &work->rotation, &dir);
        VEC_Add_01ff9e0c(&center, &dir, &pos);
        pos.y += def->height;
        dir.y = 0;
        if (VEC_DotProduct_01ff9e6c(&dir, &dir) > def->minDistanceSq) {
            VEC_Normalize_01ff9f88(&dir, &dir);
            work->speed += def->accel;
            VEC_MultAdd_01ffa09c(-work->speed, &dir, &pos, &pos);
        }
        ClearActorMotionState_02091194(actor);
        ClearActorMotionSpeed_020911a8(actor);
        VEC_Subtract_01ff9e3c(&pos, func_ov001_02090f04(actor), &dir);
        AddObjectOffsetVector_02091c50(actor, &dir);
        return TRUE;
    }
    return FALSE;
}
