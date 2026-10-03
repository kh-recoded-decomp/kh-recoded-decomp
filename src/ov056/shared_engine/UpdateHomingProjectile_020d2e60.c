#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct {
    u32 flags;
    s32 side;
    s32 strength;
    VecFx32 position;
    u8 pad_18[0xbc];
} HitResult;

typedef struct EntryInfo EntryInfo;
struct EntryInfo {
    u8 pad_000[0x228];
    int (*getAimPoint)(EntryInfo *info, VecFx32 *out);
};

typedef struct {
    u32 flags;
    u8 pad_04[4];
    s16 turnRate;
    u8 pad_0a[0xa];
    fx32 speed;
    fx32 range;
    s32 lifetime;
    u8 pad_20[8];
    s32 homingDelay;
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
} Projectile;

typedef struct {
    s32 entryIndex;
} ProjectileOwner;

extern EntryInfo *GetBoundedEntryField_0206db5c(int index);
extern VecFx32 SteerTowardTarget_020ab1f0(ProjectileOwner *owner, Projectile *proj, fx32 step);
extern fx32 FixedPointMultiply12(fx32 a, fx32 b);
extern void VEC_Subtract_01ff9e3c(const VecFx32 *a, const VecFx32 *b, VecFx32 *dst);
extern fx32 VEC_DotProduct_01ff9e6c(const VecFx32 *a, const VecFx32 *b);
extern void func_01ffaff4(const VecFx32 *src, VecFx32 *dst);
extern void ScaleVecFx32_01ffafb4(fx32 scale, const VecFx32 *src, VecFx32 *dst);
extern void VEC_MultAdd_01ffa09c(fx32 scale, const VecFx32 *v, const VecFx32 *add, VecFx32 *dst);
extern void VEC_Add_01ff9e0c(const VecFx32 *a, const VecFx32 *b, VecFx32 *ab);
extern fx32 func_01ffa0f4(const VecFx32 *a, const VecFx32 *b);
extern HitResult FindStrongestHit_020ab0c8(ProjectileOwner *owner, Projectile *proj, VecFx32 *pos, VecFx32 *vel);
extern s16 AdvanceOwnerAnimation_020ab41c(Projectile *proj, fx32 step);
extern void AdvanceToSecondPhase_020ab5f0(Projectile *proj);

BOOL UpdateHomingProjectile_020d2e60(ProjectileOwner *owner, Projectile *proj, fx32 step)
{
    HitResult hit;
    VecFx32 pos;
    VecFx32 vel;
    VecFx32 diff;
    VecFx32 aim;
    ProjectileDef *def;
    EntryInfo *target;
    fx32 blend;
    int found;
    BOOL done;
    s16 animDone;

    def = proj->def;
    proj->timer += step;
    pos = proj->position;
    vel = SteerTowardTarget_020ab1f0(owner, proj, step);
    blend = def->turnRate;
    if (proj->timer >= def->homingDelay) {
        blend += FixedPointMultiply12(4, proj->timer - def->homingDelay);
        if (blend >= 0x1000) {
            blend = 0x1000;
        }
    }
    target = GetBoundedEntryField_0206db5c(owner->entryIndex);
    if (target->getAimPoint != NULL) {
        found = target->getAimPoint(target, &aim);
    } else {
        found = 0;
    }
    if (found && proj->timer >= def->homingDelay && blend > 0 && !(def->flags & 0x100)) {
        VEC_Subtract_01ff9e3c(&aim, &pos, &diff);
        if (VEC_DotProduct_01ff9e6c(&diff, &proj->velocity) >= -0xa00) {
            func_01ffaff4(&diff, &diff);
            func_01ffaff4(&proj->velocity, &proj->velocity);
            ScaleVecFx32_01ffafb4(blend, &diff, &diff);
            VEC_MultAdd_01ffa09c(0x1000 - blend, &proj->velocity, &diff, &proj->velocity);
            func_01ffaff4(&proj->velocity, &proj->velocity);
            ScaleVecFx32_01ffafb4(def->speed, &proj->velocity, &proj->velocity);
        }
    }
    vel = proj->velocity;
    if (vel.y < 0 && proj->timer < def->homingDelay) {
        proj->velocity.y += (proj->timer >> 12) * 0x3d;
        if (proj->velocity.y > 0) {
            proj->velocity.y = 0;
        }
    }
    hit = FindStrongestHit_020ab0c8(owner, proj, &pos, &vel);
    VEC_Add_01ff9e0c(&pos, &vel, &pos);
    proj->position = pos;
    if (proj->phase == 1) {
        done = FALSE;
        animDone = AdvanceOwnerAnimation_020ab41c(proj, step);
        if (def->lifetime >= 0) {
            if (proj->timer >= def->lifetime) {
                done = TRUE;
            }
        } else if (animDone) {
            done = TRUE;
        }
        if (def->range >= 0 && func_01ffa0f4(&proj->origin, &pos) > def->range) {
            done = TRUE;
        }
        if (hit.flags & 1) {
            done = TRUE;
        }
        if (done) {
            AdvanceToSecondPhase_020ab5f0(proj);
        }
    }
    if (proj->phase == -1) {
        return TRUE;
    }
    return FALSE;
}
