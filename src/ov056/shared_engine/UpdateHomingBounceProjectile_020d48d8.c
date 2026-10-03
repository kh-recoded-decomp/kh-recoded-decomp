#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct {
    s32 target;
    s32 side;
    s32 strength;
    VecFx32 position;
    u8 pad_18[0xbc];
} HitResult;

typedef struct {
    u8 id;
    u8 pad_01[3];
    VecFx32 pos;
    u8 pad_10[0x1c];
} MarkerRequest;

typedef struct EntryInfo EntryInfo;
struct EntryInfo {
    u8 pad_000[0x228];
    int (*getAimPoint)(EntryInfo *info, VecFx32 *out);
};

typedef struct {
    s8 count;
    u8 pad_01[3];
    s32 interval;
    s32 nextTime;
} BounceState;

typedef struct {
    u8 pad_00[0x14];
    fx32 speed;
    fx32 range;
} ProjectileDef;

typedef struct {
    u8 pad_00[2];
    s8 phase;
    u8 pad_03;
    s32 timer;
    u8 pad_08[0x10];
    VecFx32 origin;
    VecFx32 velocity;
    u8 pad_30[0xd4 - 0x30];
    VecFx32 position;
    u8 pad_e0[0x138 - 0xe0];
    ProjectileDef *def;
    u8 pad_13c[2];
    s16 hitIds[8];
    u8 pad_14e[2];
    BounceState *bounce;
} Projectile;

typedef struct {
    s32 entryIndex;
    u8 pad_004[0x18e];
    s16 groupId;
} ProjectileOwner;

extern EntryInfo *GetBoundedEntryField_0206db5c(int index);
extern void VEC_Subtract_01ff9e3c(const VecFx32 *a, const VecFx32 *b, VecFx32 *dst);
extern void func_01ff9f88(const VecFx32 *src, VecFx32 *dst);
extern void ScaleVecFx32_01ffafb4(fx32 scale, const VecFx32 *src, VecFx32 *dst);
extern void VEC_Add_01ff9e0c(const VecFx32 *a, const VecFx32 *b, VecFx32 *ab);
extern fx32 func_01ffa0f4(const VecFx32 *a, const VecFx32 *b);
extern void func_ov021_020a8ab4(MarkerRequest *request);
extern int func_ov021_020a8ca0(MarkerRequest *request, int groupId);
extern HitResult FindStrongestHit_020ab0c8(ProjectileOwner *owner, Projectile *proj, VecFx32 *pos, VecFx32 *vel);
extern s16 AdvanceOwnerAnimation_020ab41c(Projectile *proj, fx32 step);
extern void AdvanceToSecondPhase_020ab5f0(Projectile *proj);

BOOL UpdateHomingBounceProjectile_020d48d8(ProjectileOwner *owner, Projectile *proj, fx32 step)
{
    HitResult hit;
    VecFx32 pos;
    VecFx32 vel;
    VecFx32 aim;
    VecFx32 dir;
    MarkerRequest request;
    ProjectileDef *def;
    BounceState *bounce;
    EntryInfo *target;
    int time;
    int found;
    int i;

    def = proj->def;
    bounce = proj->bounce;
    time = proj->timer + step;
    proj->timer = time;
    pos = proj->position;
    vel = proj->velocity;
    if (time >= bounce->nextTime && bounce->count > 0) {
        target = GetBoundedEntryField_0206db5c(owner->entryIndex);
        if (target->getAimPoint != NULL) {
            found = target->getAimPoint(target, &aim);
        } else {
            found = 0;
        }
        if (found) {
            VEC_Subtract_01ff9e3c(&aim, &pos, &dir);
            func_01ff9f88(&dir, &dir);
            ScaleVecFx32_01ffafb4(def->speed, &dir, &proj->velocity);
            proj->velocity.y /= 2;
            bounce->count--;
            proj->phase = 0;
            proj->timer = 0x1000;
            bounce->nextTime = bounce->interval;
            for (i = 0; i < 8; i++) {
                proj->hitIds[i] = -1;
            }
            func_ov021_020a8ab4(&request);
            request.id = owner->entryIndex;
            request.pos = pos;
            func_ov021_020a8ca0(&request, owner->groupId);
        }
    }
    ScaleVecFx32_01ffafb4(step, &vel, &vel);
    VEC_Add_01ff9e0c(&pos, &vel, &pos);
    proj->position = pos;
    hit = FindStrongestHit_020ab0c8(owner, proj, &pos, &vel);
    if (proj->phase == 1) {
        if (func_01ffa0f4(&proj->origin, &pos) > def->range ||
            (proj->timer >= bounce->nextTime && bounce->count == 0)) {
            AdvanceToSecondPhase_020ab5f0(proj);
        }
        AdvanceOwnerAnimation_020ab41c(proj, step);
    }
    if (proj->phase == -1) {
        return TRUE;
    }
    return FALSE;
}
