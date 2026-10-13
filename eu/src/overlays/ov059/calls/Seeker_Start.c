#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct TargetKey {
    union {
        void *object;
        struct { u16 eventId; u16 slot; } event;
    } value;
    s32 type;
} TargetKey;
typedef struct AnimationBlendTable {
    s16 animationCounts[5];
    u8 reserved0A[6];
    void **animationChoices[5];
} AnimationBlendTable;
typedef struct SeekerState {
    s32 kind;
    VecFx32 up;
    TargetKey target;
    fx32 duration;
    u32 flags;
    fx32 animationTime;
    u8 pending;
    u8 reserved25[3];
    fx32 timer;
    fx32 interval;
    fx32 boostTime;
    fx32 boostDuration;
    VecFx32 lastTargetPosition;
    fx32 baseSpeed;
} SeekerState;
typedef struct Seeker {
    u8 reserved00[2];
    s8 status;
    u8 reserved03[0x2d];
    u8 animation[0xa4];
    VecFx32 position;
    u8 reservedE0[0x28];
    AnimationBlendTable jointBlend;
    u8 reserved12C[0x24];
    SeekerState *state;
} Seeker;
typedef struct SeekerPool {
    u8 reserved00[8];
    Seeker *seekers;
    u8 reserved0C[9];
    u8 capacity;
    u8 reserved16[0x26];
    SeekerState *states;
    u8 reserved40[4];
    void *world;
} SeekerPool;
typedef struct SeekerSpawnParams {
    s32 kind;
    VecFx32 position;
    VecFx32 velocity;
    TargetKey target;
    fx32 duration;
    fx32 timer;
    fx32 interval;
    fx32 boostDuration;
} SeekerSpawnParams;
typedef struct LimitedUseTarget {
    VecFx32 position;
    VecFx32 velocity;
    fx32 duration;
    u8 reserved1C[0x10];
    u32 flags;
    u8 reserved30[8];
    u32 auxiliary;
    s32 slotIndex;
} LimitedUseTarget;

extern void ZeroBytes0x40(LimitedUseTarget *);
extern BOOL TryConsumeLimitedUse(SeekerPool *, LimitedUseTarget *);
extern void Seeker_SelectNearestTarget(Seeker *, void *world);
extern int MapStateToOddIndex(SeekerState *);
extern void selectJointAnimationBlend(void *animation, u16 index,
                                      const AnimationBlendTable *blend, s16 blendIndex);
extern fx32 VEC_Mag(const VecFx32 *);
extern void TargetKey_GetPosition(VecFx32 *, const TargetKey *);
extern u32 random_next_scaled(u32 upperBound);
extern void SpawnSoundSlot(int sound, int flags, const VecFx32 *, int extra);

SeekerState *Seeker_Start(SeekerPool *pool, const SeekerSpawnParams *params)
{
    LimitedUseTarget target;
    VecFx32 targetPosition;
    VecFx32 initialUp;
    int index;
    int count = pool->capacity;

    for (index = 0; index < count; index++) {
        Seeker *seeker = &pool->seekers[index];
        if (seeker->status == -1) {
            SeekerState *state = &pool->states[index];
            u32 flags;
            seeker->state = state;
            ZeroBytes0x40(&target);
            target.position = params->position;
            target.velocity = params->velocity;
            flags = 0;
            target.duration = params->duration;
            target.flags = 0;
            target.auxiliary = 0;
            if (!TryConsumeLimitedUse(pool, &target)) {
                goto done;
            }
            state->kind = params->kind;
            state->duration = params->duration;
            state->timer = params->timer;
            state->interval = params->interval;
            state->boostTime = params->boostDuration;
            state->boostDuration = params->boostDuration;
            if (state->kind == 2) {
                flags = 4;
            }
            state->flags = 0x400 | flags;
            state->animationTime = 0;
            state->pending = 1;
            initialUp.x = 0;
            initialUp.y = 0x1000;
            initialUp.z = 0;
            state->up = initialUp;
            if (params->target.type == 0) {
                Seeker_SelectNearestTarget(seeker, pool->world);
            } else {
                state->target = params->target;
            }
            /* Keep the startup lookup even though its result is not used here. */
            MapStateToOddIndex(state);
            switch (state->kind) {
            case 1:
                selectJointAnimationBlend(seeker->animation, 0, &seeker->jointBlend, 0);
                selectJointAnimationBlend(seeker->animation, 2, &seeker->jointBlend, 0);
                break;
            case 2:
                selectJointAnimationBlend(seeker->animation, 0, &seeker->jointBlend, 1);
                selectJointAnimationBlend(seeker->animation, 2, &seeker->jointBlend, 1);
                break;
            case 0:
            case 3:
            case 4:
                break;
            }
            switch (state->kind) {
            case 2:
                state->baseSpeed = VEC_Mag(&params->velocity);
                TargetKey_GetPosition(&targetPosition, &state->target);
                state->lastTargetPosition = targetPosition;
                break;
            case 4:
                state->interval = random_next_scaled(0x9c6) + 0x5000;
                SpawnSoundSlot(0xcb, 0, &seeker->position, 0);
                break;
            case 0:
            case 1:
            case 3:
                break;
            }
done:
            return state;
        }
    }
    return NULL;
}
