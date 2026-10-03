#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct {
    s32 target;
    s32 side;
    s32 strength;
    u8 pad_0c[0xc8];
} HitResult;

typedef struct {
    u8 pad_00[0x94];
    u16 facing;
    u8 pad_96[0xbc - 0x96];
    VecFx32 position;
} EntryInfo;

typedef struct {
    u8 pad_00[0x24];
    s32 lifetime;
} ProjectileDef;

typedef struct {
    u8 pad_00[2];
    s8 phase;
    u8 pad_03;
    s32 timer;
    u8 pad_08[0x1c];
    VecFx32 velocity;
    u8 pad_30[0xd4 - 0x30];
    VecFx32 position;
    u8 pad_e0[0x138 - 0xe0];
    ProjectileDef *def;
} Projectile;

typedef struct {
    s32 entryIndex;
} ProjectileOwner;

extern s16 data_0205356c[];
extern EntryInfo *GetBoundedEntryField_0206db5c(int index);
extern void VEC_MultAdd_01ffa09c(fx32 scale, const VecFx32 *v, const VecFx32 *add, VecFx32 *dst);
extern void VEC_Subtract_01ff9e3c(const VecFx32 *a, const VecFx32 *b, VecFx32 *ab);
extern void VEC_Normalize_01ff9f88(const VecFx32 *src, VecFx32 *dst);
extern HitResult FindStrongestHit_020ab0c8(ProjectileOwner *owner, Projectile *proj, VecFx32 *pos, VecFx32 *vel);
extern s16 AdvanceOwnerAnimation_020ab41c(Projectile *proj, fx32 step);

BOOL UpdateSweepProjectile_020d47e0(ProjectileOwner *owner, Projectile *proj, fx32 step)
{
    ProjectileDef *def = proj->def;
    EntryInfo *info;
    HitResult hit;
    VecFx32 pos;
    VecFx32 dir;
    u16 angle;
    int index;

    if (proj->timer == 0) {
        info = GetBoundedEntryField_0206db5c(owner->entryIndex);
        angle = info->facing - 0x8000;
        pos = info->position;
        pos.y += 0xc00;
        index = angle >> 4;
        dir.x = data_0205356c[index];
        dir.y = 0;
        dir.z = data_0205356c[(0x400 - index) & 0xfff];
        VEC_MultAdd_01ffa09c(0x800, &dir, &pos, &pos);
        VEC_Subtract_01ff9e3c(&proj->position, &pos, &dir);
    } else {
        pos = proj->position;
        VEC_Normalize_01ff9f88(&proj->velocity, &dir);
    }
    hit = FindStrongestHit_020ab0c8(owner, proj, &pos, &dir);
    proj->timer += step;
    if (proj->timer >= def->lifetime && proj->phase == 0) {
        proj->timer = 0;
        proj->phase = 1;
    }
    if (proj->phase == 0) {
        AdvanceOwnerAnimation_020ab41c(proj, step);
    }
    if (proj->phase == -1) {
        return TRUE;
    }
    return FALSE;
}
