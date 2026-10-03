#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct {
    VecFx32 position;
    u8 pad_0c[0xc];
    s32 paramA;
    s32 paramB;
    u8 pad_20[4];
    s32 paramC;
    u8 pad_28[4];
    s32 delay;
    u32 variant;
    s32 kind;
    s32 active;
    s32 slotIndex;
} ShotRecord;

typedef struct ShotManager {
    u8 pad_000[0x228];
    BOOL (*getTarget)(struct ShotManager *manager, VecFx32 *out);
} ShotManager;

typedef struct {
    u8 pad_000[0x3c];
    s8 actorId;
    u8 pad_03d[0x13b];
    s32 paramA;
    s32 paramB;
    s32 paramC;
    u8 pad_184[4];
    s16 soundId;
    u8 pad_18a[6];
    s8 pattern;
    s8 shotLimit;
    u8 pad_192[6];
    s32 spread;
    fx32 homing;
} ShotEmitter;

typedef struct {
    s8 count;
    u8 pad_01[3];
    s32 timer;
    u16 angle;
    u8 pad_0a[2];
    VecFx32 position;
    s8 kind;
    u8 variant;
    u8 pad_1a[6];
    s32 lastShot;
} ShotState;

extern const s16 data_0205356c[];

extern void ZeroBytes0x40_020ab08c(ShotRecord *record);
extern VecFx32 *func_ov001_0206dc4c(int actorId);
extern ShotManager *GetBoundedEntryField_0206db5c(int index);
extern u32 random_next_scaled_0202aa04(u32 upperBound);
extern void VEC_Add_01ff9e0c(const VecFx32 *a, const VecFx32 *b, VecFx32 *out);
extern void VEC_Subtract_01ff9e3c(const VecFx32 *a, const VecFx32 *b, VecFx32 *out);
extern fx32 func_01ffaff4(const VecFx32 *src, VecFx32 *dst);
extern void ScaleVecFx32_01ffafb4(fx32 scale, const VecFx32 *src, VecFx32 *dst);
extern void VEC_MultAdd_01ffa09c(fx32 scale, const VecFx32 *v, const VecFx32 *add, VecFx32 *dst);
extern void SweepDropToGround_020ae3f0(ShotRecord *out, u32 actorId, const VecFx32 *position, const VecFx32 *delta, fx32 radius, u32 matchFlag);
extern u16 FixedPointAtan2_020062bc(fx32 y, fx32 x);
extern u32 SpawnSoundSlot_0204da8c(u32 owner, u32 kind, VecFx32 *position, u32 flags);
extern int TryConsumeLimitedUse_020ab098(ShotEmitter *emitter, ShotRecord *record);

static inline BOOL QueryTarget(ShotManager *manager, VecFx32 *out)
{
    if (manager->getTarget != NULL) {
        return manager->getTarget(manager, out);
    }
    return FALSE;
}

void SpawnPatternShot_020ae0f8(ShotEmitter *emitter, ShotState *state, fx32 radius)
{
    ShotRecord record;
    VecFx32 origin;
    VecFx32 dir;
    VecFx32 target;
    VecFx32 toTarget;
    fx32 homing;
    s32 range;
    int shot;

    ZeroBytes0x40_020ab08c(&record);
    record.active = 1;
    switch (emitter->pattern) {
    case 0: {
        origin = *func_ov001_0206dc4c(emitter->actorId);
        dir.z = 0;
        dir.y = 0;
        dir.x = 0;
        {
            VecFx32 jitter;
            s32 spread = emitter->spread;

            jitter.x = random_next_scaled_0202aa04(spread) - spread / 2;
            jitter.z = random_next_scaled_0202aa04(spread) - spread / 2;
            jitter.y = 0;
            VEC_Add_01ff9e0c(&origin, &jitter, &origin);
        }
        SweepDropToGround_020ae3f0(&record, emitter->actorId, &origin, &dir, radius, 0);
        break;
    }
    case 1: {
        int index;
        u16 heading;

        homing = emitter->homing;
        range = emitter->spread;
        origin = state->position;
        index = state->angle >> 4;
        dir.x = data_0205356c[index];
        dir.y = 0;
        dir.z = data_0205356c[(0x400 - index) & 0xfff];
        if (QueryTarget(GetBoundedEntryField_0206db5c(emitter->actorId), &target)) {
            VEC_Subtract_01ff9e3c(&target, &origin, &toTarget);
            func_01ffaff4(&toTarget, &toTarget);
            func_01ffaff4(&dir, &dir);
            ScaleVecFx32_01ffafb4(homing, &toTarget, &toTarget);
            VEC_MultAdd_01ffa09c(0x1000 - homing, &dir, &toTarget, &dir);
            func_01ffaff4(&dir, &dir);
        }
        VEC_MultAdd_01ffa09c(-0x800, &dir, &origin, &origin);
        ScaleVecFx32_01ffafb4(range + 0x800, &dir, &dir);
        SweepDropToGround_020ae3f0(&record, emitter->actorId, &origin, &dir, radius, 0);
        state->position = record.position;
        heading = FixedPointAtan2_020062bc(dir.x, dir.z) + 0x8000;
        state->angle = heading + 0x8000;
        SpawnSoundSlot_0204da8c(emitter->soundId, 2, &state->position, 2);
        break;
    }
    case 2: {
        u16 angle = state->angle;
        int index;

        origin = state->position;
        if (state->count % 2 != 0) {
            angle -= 0x8000;
        }
        index = angle >> 4;
        dir.y = 0;
        dir.x = data_0205356c[index];
        dir.z = data_0205356c[(0x400 - index) & 0xfff];
        VEC_MultAdd_01ffa09c((state->count / 2) * 0x1000 + 0x1000, &dir, &origin, &origin);
        dir.z = 0;
        dir.y = 0;
        dir.x = 0;
        SweepDropToGround_020ae3f0(&record, emitter->actorId, &origin, &dir, radius, 1);
        break;
    }
    case 3: {
        target.z = 0;
        target.y = 0;
        target.x = 0;
        origin = *func_ov001_0206dc4c(emitter->actorId);
        if (QueryTarget(GetBoundedEntryField_0206db5c(0), &target)) {
            origin = target;
        }
        dir.z = 0;
        dir.y = 0;
        dir.x = 0;
        if (state->count != 0 || (target.x == 0 && target.y == 0 && target.z == 0)) {
            VecFx32 jitter;
            s32 spread = emitter->spread;

            jitter.x = random_next_scaled_0202aa04(spread) - spread / 2;
            jitter.z = random_next_scaled_0202aa04(spread) - spread / 2;
            jitter.y = 0;
            VEC_Add_01ff9e0c(&origin, &jitter, &origin);
        }
        SweepDropToGround_020ae3f0(&record, emitter->actorId, &origin, &dir, radius, 0);
        break;
    }
    }
    record.delay = 0;
    record.paramA = emitter->paramA;
    record.paramB = emitter->paramB;
    record.paramC = emitter->paramC;
    record.kind = state->kind;
    record.variant = state->variant;
    shot = TryConsumeLimitedUse_020ab098(emitter, &record);
    if (shot != 0) {
        state->timer = 0;
        state->count++;
        if (state->count == emitter->shotLimit) {
            state->lastShot = shot;
        }
    }
}
