#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct Entity Entity;

typedef void (*EntityEventFunc)(Entity *entity, int event, int value);
typedef void (*EntityAngleFunc)(Entity *entity, u16 angle);
typedef BOOL (*EntityTargetFunc)(Entity *entity, VecFx32 *target);
typedef void (*EntityStateHandler)(Entity *entity);

struct Entity {
    u8 pad_000[0x1f8];
    EntityEventFunc onEvent;
    u8 pad_1fc[0x210 - 0x1fc];
    EntityAngleFunc setAngle;
    u8 pad_214[0x228 - 0x214];
    EntityTargetFunc getTarget;
    u8 pad_22c[0x234 - 0x22c];
    u32 attributes;
    u8 pad_238[0x9ac - 0x238];
    u64 stateFlags;
    u8 slot;
    u8 pad_9b5[7];
    EntityStateHandler stateHandler;
};

extern void *func_ov001_0206db78(u8 slot);
extern int func_ov052_020ccfa4(Entity *entity, int state, int force);
extern int func_ov052_020cd338(Entity *entity, int state);
extern VecFx32 *func_ov052_020ceb54(Entity *entity);
extern void VEC_Subtract_01ff9e3c(const VecFx32 *a, const VecFx32 *b, VecFx32 *out);
extern u16 FixedPointAtan2_020062bc(fx32 y, fx32 x);
extern u32 SpawnSoundSlot_0204da8c(u32 owner, u32 kind, VecFx32 *position, u32 flags);
extern void Entity_UpdateSpecialRelease_020a1298(Entity *entity);
extern void Entity_UpdateSpecialCharge_020a1708(Entity *entity);

static inline BOOL Vec_IsPlanarZero(const VecFx32 *vec)
{
    return vec->x == 0 && vec->y == 0;
}

int Entity_ChangeSpecialState_020a1978(Entity *entity, int state)
{
    BOOL handled;
    u32 charged;
    int result;
    VecFx32 target;
    VecFx32 delta;
    fx32 deltaX;
    BOOL nonZero;
    BOOL planarNonZero;

    func_ov001_0206db78(entity->slot);
    charged = entity->attributes & 4;
    result = state;
    handled = FALSE;
    if (result == 0x1e && !func_ov052_020ccfa4(entity, result, 0)) {
        handled = TRUE;
        if (charged) {
            entity->stateFlags |= 0x1000000;
            entity->stateFlags |= 0x40;
            entity->stateHandler = Entity_UpdateSpecialRelease_020a1298;
            if (entity->onEvent != NULL) {
                entity->onEvent(entity, 0x17, -1);
            }
            if (entity->getTarget != NULL ? entity->getTarget(entity, &target) : FALSE) {
                VEC_Subtract_01ff9e3c(&target, func_ov052_020ceb54(entity), &delta);
                nonZero = TRUE;
                planarNonZero = TRUE;
                deltaX = delta.x;
                if (Vec_IsPlanarZero(&delta)) {
                    planarNonZero = FALSE;
                }
                if (!planarNonZero && delta.z == 0) {
                    nonZero = FALSE;
                }
                if (nonZero) {
                    u16 angle = FixedPointAtan2_020062bc(deltaX, delta.z) + 0x8000;
                    if (entity->setAngle != NULL) {
                        entity->setAngle(entity, angle);
                    }
                }
            }
            SpawnSoundSlot_0204da8c(0x35, 0, func_ov052_020ceb54(entity), 0);
            result = 0x1e;
        } else {
            entity->stateHandler = Entity_UpdateSpecialCharge_020a1708;
            result = 0x1f;
        }
    }
    if (!handled) {
        result = func_ov052_020cd338(entity, state);
    }
    return result;
}
