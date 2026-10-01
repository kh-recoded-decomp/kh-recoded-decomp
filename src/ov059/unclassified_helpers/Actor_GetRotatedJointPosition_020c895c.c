#include "nitro/types.h"
#include "nitro/fx_types.h"
#include "nitro/fx.h"

typedef struct ModelInstance {
    u8 pad_00[0x7e];
    u16 pitch;
} ModelInstance;

typedef struct ActorModel {
    u32 flags;
    ModelInstance instance;
} ActorModel;

typedef struct Actor {
    u8 pad_000[0x230];
    ActorModel *model;
} Actor;

extern const s16 data_0205356c[];

extern int func_ov059_020cd0e4(Actor *actor);
extern void func_ov059_020c8908(VecFx32 *out, Actor *actor, int jointIndex);
extern void MTX_RotZ33_01ff9258(MtxFx33 *mtx, fx32 sinVal, fx32 cosVal);
extern void MTX_RotY33_01ff923c(MtxFx33 *mtx, fx32 sinVal, fx32 cosVal);
extern void MTX_MultVec33_01ff9404(const VecFx32 *vec, const MtxFx33 *mtx, VecFx32 *dst);
extern VecFx32 *Actor_GetModelPosition_020cd0d8(Actor *actor);
extern void VEC_Add_01ff9e0c(const VecFx32 *a, const VecFx32 *b, VecFx32 *ab);

void Actor_GetRotatedJointPosition_020c895c(VecFx32 *out, Actor *actor)
{
    VecFx32 result;
    VecFx32 offset;
    VecFx32 baseJoint;
    MtxFx33 yawRotation;
    MtxFx33 pitchRotation;
    ModelInstance *instance = &actor->model->instance;
    int heading = func_ov059_020cd0e4(actor);
    int angleIndex;

    func_ov059_020c8908(&baseJoint, actor, 2);
    func_ov059_020c8908(&offset, actor, 3);
    angleIndex = instance->pitch >> 4;
    MTX_RotZ33_01ff9258(&pitchRotation, data_0205356c[angleIndex], data_0205356c[(0x400 - angleIndex) & 0xfff]);
    angleIndex = heading >> 4;
    MTX_RotY33_01ff923c(&yawRotation, -data_0205356c[angleIndex], -data_0205356c[(0x400 - angleIndex) & 0xfff]);
    MTX_MultVec33_01ff9404(&offset, &pitchRotation, &offset);
    MTX_MultVec33_01ff9404(&offset, &yawRotation, &offset);
    VEC_Add_01ff9e0c(&offset, Actor_GetModelPosition_020cd0d8(actor), &result);
    *out = result;
}
