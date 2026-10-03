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
    u8 pad_00[0x94];
    u16 yaw;
    u8 pad_96[0x26];
    VecFx32 position;
} PartyEntry;

typedef struct {
    u8 pad_00[0x24];
    s32 duration;
} UnitType;

typedef struct {
    u8 pad_000[2];
    s8 state;
    u8 pad_003;
    s32 timer;
    u8 pad_008[0x1c];
    VecFx32 direction;
    u8 pad_030[0xa4];
    VecFx32 position;
    u8 pad_0e0[0x58];
    UnitType *type;
} Unit;

typedef struct {
    s32 player;
} Attacker;

extern const s16 data_0205356c[];
extern PartyEntry *GetBoundedEntryField_0206db5c(int index);
extern void VEC_MultAdd_01ffa09c(fx32 a, const VecFx32 *v1, const VecFx32 *v2, VecFx32 *dst);
extern void VEC_Subtract_01ff9e3c(const VecFx32 *a, const VecFx32 *b, VecFx32 *ab);
extern void VEC_Normalize_01ff9f88(const VecFx32 *src, VecFx32 *dst);
extern s16 AdvanceOwnerAnimation_020ab41c(Unit *owner, fx32 step);
extern HitResult FindStrongestHit_020ab0c8(Attacker *attacker, Unit *unit, VecFx32 *position, VecFx32 *direction);

BOOL UpdateUnitAttackSweep_020ae73c(Attacker *attacker, Unit *unit, fx32 step) {
    UnitType *type = unit->type;
    PartyEntry *entry = GetBoundedEntryField_0206db5c(attacker->player);
    HitResult hit;
    VecFx32 pos;
    VecFx32 dir;
    if (unit->timer == 0) {
        u16 yaw = (u16)(entry->yaw - 0x8000);
        int index;
        pos = entry->position;
        pos.y += 0xc00;
        index = yaw >> 4;
        dir.x = data_0205356c[index];
        dir.y = 0;
        dir.z = data_0205356c[(0x400 - index) & 0xfff];
        VEC_MultAdd_01ffa09c(0x800, &dir, &pos, &pos);
        VEC_Subtract_01ff9e3c(&unit->position, &pos, &dir);
        dir.y = 0;
    } else {
        pos = unit->position;
        VEC_Normalize_01ff9f88(&unit->direction, &dir);
    }
    AdvanceOwnerAnimation_020ab41c(unit, step);
    hit = FindStrongestHit_020ab0c8(attacker, unit, &pos, &dir);
    if (unit->state == 0) {
        unit->timer += step;
        if (unit->timer >= type->duration) {
            unit->timer = 0;
            unit->state = 1;
        }
    } else if (unit->state == 2 && hit.strength == 1) {
        unit->position = hit.position;
    }
    if (unit->state == -1) {
        return TRUE;
    }
    return FALSE;
}
