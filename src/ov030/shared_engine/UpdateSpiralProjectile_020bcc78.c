#include "nitro/types.h"
#include "nitro/fx_types.h"
#include "nitro/fx.h"

typedef struct {
    s32 target;
    s32 side;
    s32 strength;
    u8 pad_0c[0xc8];
} HitResult;

typedef struct {
    u8 pad_00[0x18];
    fx32 maxRange;
    s32 lifetime;
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
    u8 pad_000[0x1c0];
    s32 turnInterval;
} ProjectileOwner;

extern const s16 data_0205356c[];
extern void MTX_RotZ33_01ff9258(MtxFx33 *mtx, fx32 sinVal, fx32 cosVal);
extern void MTX_MultVec33_01ff9404(const VecFx32 *vec, const MtxFx33 *mtx, VecFx32 *dst);
extern void VEC_Add_01ff9e0c(const VecFx32 *a, const VecFx32 *b, VecFx32 *ab);
extern fx32 func_01ffa0f4(const VecFx32 *a, const VecFx32 *b);
extern HitResult FindStrongestHit_020ab0c8(ProjectileOwner *owner, Projectile *proj, VecFx32 *pos, VecFx32 *vel);
extern s16 AdvanceOwnerAnimation_020ab41c(Projectile *proj, fx32 step);
extern void AdvanceToSecondPhase_020ab5f0(Projectile *proj);

BOOL UpdateSpiralProjectile_020bcc78(ProjectileOwner *owner, Projectile *proj, fx32 step)
{
    ProjectileDef *def = proj->def;
    VecFx32 pos;
    VecFx32 vel;
    MtxFx33 rot;
    u16 angle;
    int index;
    BOOL finished;

    proj->timer += step;
    pos = proj->position;
    vel = proj->velocity;
    if (proj->timer % owner->turnInterval == 0) {
        angle = 0x1c70;
        if (vel.y >= 0) {
            angle = 0xe38f;
        }
        if (vel.x < 0) {
            angle = 0xffff - angle;
        }
        index = angle >> 4;
        MTX_RotZ33_01ff9258(&rot, data_0205356c[index], data_0205356c[(0x400 - index) & 0xfff]);
        MTX_MultVec33_01ff9404(&proj->velocity, &rot, &proj->velocity);
    }
    VEC_Add_01ff9e0c(&pos, &vel, &pos);
    proj->position = pos;
    FindStrongestHit_020ab0c8(owner, proj, &pos, &vel);
    if (proj->phase == 1) {
        finished = FALSE;
        AdvanceOwnerAnimation_020ab41c(proj, step);
        if (def->lifetime >= 0 && proj->timer >= def->lifetime) {
            finished = TRUE;
        }
        if (def->maxRange >= 0 && func_01ffa0f4(&proj->origin, &pos) > def->maxRange) {
            finished = TRUE;
        }
        if (finished) {
            AdvanceToSecondPhase_020ab5f0(proj);
        }
    }
    if (proj->phase == -1) {
        return TRUE;
    }
    return FALSE;
}
