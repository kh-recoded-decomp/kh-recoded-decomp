#include "nitro/types.h"
#include "nitro/fx_types.h"
#include "nitro/fx.h"

typedef struct {
    s16 animId;
    u8 pad_02[0x2a];
} QueuedAnim;

typedef struct {
    u8 pad_000[0x5d0];
    QueuedAnim queue[7];
    u8 pad_704[0x114];
    s32 timer;
    s32 timerLimit;
    u8 pad_820[0x4c];
    fx32 moveScale;
    u8 pad_870[0x24];
    u8 rootMotion[0x370];
    u8 anim[0xd8];
    u8 blend[0x2c];
    VecFx32 blendOffset;
    s32 lockHeading;
    u8 pad_D18[0x1e4];
    s32 heading;
} FieldActor;

extern const VecFx32 data_02053438;
extern const s16 data_0205356c[];

extern void ActorAnim_AdvanceAndGetRootDelta_02089118(VecFx32 *out, void *rootMotion);
extern void ScaleVecFx32_01ffafb4(fx32 scale, const VecFx32 *in, VecFx32 *out);
extern void MTX_Identity43_01ff9480(MtxFx43 *mtx);
extern void MTX_RotY43_01ff9530(MtxFx43 *mtx, fx32 sinVal, fx32 cosVal);
extern void MTX_MultVec43_01ff9ad8(const VecFx32 *vec, const MtxFx43 *mtx, VecFx32 *out);
extern void Actor_FireExpiredTrackCues_02089180(FieldActor *actor);
extern BOOL func_ov001_020645c8(int bitId);
extern int Anim_GetFrame_0202f4a0(void *anim, int track);
extern void WriteSessionPackedBits_0206459c(int bitId, int value, int arg);
extern u32 BuildSlotMask_0202f034(void *anim, int flag);
extern void func_ov001_02088b48(FieldActor *actor);
extern void selectJointAnimationBlend_0202f2cc(void *anim, int track, void *blend, int animId);
extern void func_01ffb2f8(void *anim, int track, int frame);

void ApplyActorRootMotion_02089208(FieldActor *actor, VecFx32 *out) {
    VecFx32 motion;
    MtxFx43 rotation;
    VecFx32 delta;
    int heading;
    int i;

    ActorAnim_AdvanceAndGetRootDelta_02089118(&delta, actor->rootMotion);
    motion = delta;
    heading = actor->heading;
    ScaleVecFx32_01ffafb4(actor->moveScale, &motion, &motion);
    if (actor->lockHeading == 0) {
        MTX_Identity43_01ff9480(&rotation);
        heading >>= 4;
        MTX_RotY43_01ff9530(&rotation, data_0205356c[heading], data_0205356c[(0x400 - heading) & 0xfff]);
        MTX_MultVec43_01ff9ad8(&motion, &rotation, out);
    } else {
        *out = motion;
    }
    Actor_FireExpiredTrackCues_02089180(actor);
    if (func_ov001_020645c8(0x362a) && actor->queue[1].animId == -1 && Anim_GetFrame_0202f4a0(actor->anim, 0) >= 0x8000) {
        if (actor->heading < 0x8000) {
            actor->heading = 0x2000;
        } else {
            actor->heading = 0xe000;
        }
        actor->timerLimit = -1;
        actor->timer = 0x2ab8;
        WriteSessionPackedBits_0206459c(0x362a, 1, 0);
    }
    if (BuildSlotMask_0202f034(actor->anim, 0x1000)) {
        if (actor->queue[1].animId != -1) {
            actor->blendOffset = data_02053438;
            selectJointAnimationBlend_0202f2cc(actor->anim, 0, actor->blend, actor->queue[1].animId);
            func_01ffb2f8(actor->anim, 0, 0);
            actor->queue[1].animId = -1;
            for (i = 1; i < 6; i++) {
                s16 next = actor->queue[i + 1].animId;
                if (next == -1) {
                    break;
                }
                actor->queue[i].animId = next;
                actor->queue[i + 1].animId = -1;
            }
        } else {
            func_ov001_02088b48(actor);
        }
    }
}
