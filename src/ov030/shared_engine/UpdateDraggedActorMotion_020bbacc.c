#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct {
    u8 pad_00[0x3c];
    u32 flags;
    u8 pad_40[0xc];
    u16 lowBits : 6;
    u16 keepPose : 1;
    u16 highBits : 9;
    u8 pad_4e[0x42];
} AnimClip;

typedef struct {
    u8 pad_00[0x6c];
    AnimClip *clips;
    u8 pad_70[4];
    void *spawnData;
    s16 *groupId;
    u8 pad_7c[4];
    s8 memberIndex;
} AnimSet;

typedef struct {
    u16 flags;
    u8 pad_02[0x7c];
    u16 yaw;
    u8 pad_80[0x24];
    VecFx32 pos;
} GroupMember;

typedef struct {
    void *callback;
    void *owner;
    u8 pad_08[0x18];
} ClipEventContext;

typedef struct {
    u8 pad_00[8];
    fx32 damping;
    u8 pad_0c[4];
    VecFx32 velocity;
    u8 pad_1c[0x25];
    s8 clipIndex;
} DragMotion;

typedef struct DragActor DragActor;

struct DragActor {
    u8 pad_000[0xbc];
    VecFx32 pos;
    u8 pad_0c8[0x1f8 - 0xc8];
    void (*onRelease)(DragActor *actor, int a, int b);
    u8 pad_1fc[0x224 - 0x1fc];
    VecFx32 *(*getPosition)(DragActor *actor);
    u8 pad_228[0x234 - 0x228];
    u32 moveFlags;
    u8 pad_238[0x760 - 0x238];
    s32 frame;
    u8 pad_764[4];
    s32 motionActive;
    u8 pad_76c[0x9ac - 0x76c];
    u64 flags;
    u8 entryId;
    u8 pad_9b5[0x9c4 - 0x9b5];
    s32 height;
    VecFx32 offset;
    u8 pad_9d4[0xa10 - 0x9d4];
    DragMotion motion;
    u8 pad_a54[0x1030 - 0xa54];
    s32 pendingAction;
    u8 pad_1034[0x1078 - 0x1034];
    AnimSet *anim;
    u8 pad_107c[0x10ec - 0x107c];
    void (*setState)(DragActor *actor, int state);
};

extern const s16 data_0205356c[];
extern void *func_ov001_0206db78(int index);
extern BOOL IsFrameInSubObjectRange_020aa568(AnimClip *clip, s32 frame, int arg);
extern BOOL func_ov052_020d0524(DragActor *actor);
extern BOOL AlarmCallback_020a7504(void *entry);
extern fx32 func_ov052_020d0e80(DragMotion *motion);
extern void func_ov052_020cebbc(DragActor *actor, VecFx32 *dir);
extern u16 func_ov021_020a7544(void *entry);
extern fx32 func_01ffaff4(const VecFx32 *src, VecFx32 *dst);
extern void VEC_Add_01ff9e0c(const VecFx32 *a, const VecFx32 *b, VecFx32 *ab);
extern void VEC_Subtract_01ff9e3c(const VecFx32 *a, const VecFx32 *b, VecFx32 *ab);
extern fx32 FixedPointMultiply12(fx32 a, fx32 b);
extern GroupMember *GetGroupMemberData_020a8eec(int groupId, int member);
extern u16 FixedPointAtan2_020062bc(fx32 y, fx32 x);
extern void func_ov052_020d19f8(ClipEventContext *ctx, AnimClip *clip, int arg, int entryId);
extern void SpawnJitteredMarker_020bbd50(void);
extern BOOL func_ov052_020d012c(DragActor *actor, AnimClip *clip, ClipEventContext *ctx);
extern BOOL func_ov052_020d0294(DragActor *actor, AnimClip *clip, int arg);
extern BOOL func_ov052_020d03b8(DragActor *actor);

void UpdateDraggedActorMotion_020bbacc(DragActor *actor)
{
    ClipEventContext ctx;
    VecFx32 dir;
    VecFx32 facing;
    VecFx32 diff;
    void *entry = func_ov001_0206db78(actor->entryId);
    DragMotion *motion = &actor->motion;
    AnimSet *anim = actor->anim;
    AnimClip *clip = &anim->clips[motion->clipIndex];
    fx32 speed;
    u16 angle;
    int index;
    GroupMember *member;
    VecFx32 *pos;
    u32 heavy;
    u32 keepPose;

    if (!(actor->flags & 0x100) && IsFrameInSubObjectRange_020aa568(clip, actor->frame, 0) &&
        func_ov052_020d0524(actor)) {
        actor->pendingAction = 6;
        actor->flags |= 0x100;
    }
    dir.z = 0;
    dir.y = 0;
    dir.x = 0;
    if (AlarmCallback_020a7504(entry)) {
        speed = func_ov052_020d0e80(motion);
        func_ov052_020cebbc(actor, &dir);
        angle = func_ov021_020a7544(entry);
        index = angle >> 4;
        dir.x = -data_0205356c[index];
        dir.z = -data_0205356c[(0x400 - index) & 0xfff];
        func_01ffaff4(&motion->velocity, &facing);
        VEC_Add_01ff9e0c(&dir, &facing, &dir);
        func_01ffaff4(&dir, &dir);
    } else {
        dir = motion->velocity;
        speed = 0xe14;
        motion->damping = FixedPointMultiply12(motion->damping, speed);
    }
    dir.x = FixedPointMultiply12(dir.x, speed);
    dir.z = FixedPointMultiply12(dir.z, speed);
    motion->velocity = dir;
    actor->offset.x += dir.x;
    actor->offset.z += dir.z;
    if (actor->height <= 0x3000) {
        member = GetGroupMemberData_020a8eec(*anim->groupId, anim->memberIndex);
        if (actor->getPosition != NULL) {
            pos = actor->getPosition(actor);
        } else {
            pos = &actor->pos;
        }
        VEC_Subtract_01ff9e3c(pos, &member->pos, &diff);
        func_01ffaff4(&diff, &diff);
        member->yaw = FixedPointAtan2_020062bc(-diff.x, diff.y);
        member->flags |= 0x20;
    }
    func_ov052_020d19f8(&ctx, clip, 0, actor->entryId);
    if (anim->spawnData != NULL) {
        ctx.owner = anim;
        ctx.callback = SpawnJitteredMarker_020bbd50;
    }
    if (func_ov052_020d012c(actor, clip, &ctx) || func_ov052_020d0294(actor, clip, 0) || actor->motionActive == 0) {
        return;
    }
    heavy = actor->moveFlags & 4;
    keepPose = clip->keepPose;
    if (func_ov052_020d03b8(actor)) {
        return;
    }
    if (heavy) {
        if (!(clip->flags & 4)) {
            actor->setState(actor, 1);
            if (actor->onRelease != NULL) {
                actor->onRelease(actor, 0, -1);
            }
            return;
        }
        actor->setState(actor, 5);
        return;
    }
    if (keepPose == 0) {
        actor->flags |= 0x100;
    }
    actor->setState(actor, 4);
}
