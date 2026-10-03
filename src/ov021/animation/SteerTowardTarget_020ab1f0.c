#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct PartyEntry {
    u8 pad_000[0x228];
    BOOL (*getTarget)(struct PartyEntry *entry, VecFx32 *out);
} PartyEntry;

typedef struct {
    u32 flags;
    u8 pad_04[4];
    s16 turnRate;
    u8 pad_0a[0xa];
    fx32 speed;
    u8 pad_18[0x10];
    s32 homingDelay;
    fx32 decay;
} SteerDesc;

typedef struct {
    u8 pad_000[4];
    s32 time;
    u8 pad_008[0x1c];
    VecFx32 direction;
    u8 pad_030[0xa4];
    VecFx32 position;
    u8 pad_0e0[0x58];
    SteerDesc *desc;
} SteerObject;

extern PartyEntry *GetBoundedEntryField_0206db5c(int index);
extern void VEC_Subtract_01ff9e3c(const VecFx32 *a, const VecFx32 *b, VecFx32 *ab);
extern fx32 VEC_DotProduct_01ff9e6c(const VecFx32 *a, const VecFx32 *b);
extern void VEC_Normalize_01ffaff4(const VecFx32 *src, VecFx32 *dst);
extern void ScaleVecFx32_01ffafb4(fx32 scale, const VecFx32 *src, VecFx32 *dst);
extern void VEC_MultAdd_01ffa09c(fx32 a, const VecFx32 *v1, const VecFx32 *v2, VecFx32 *dst);
extern int func_02023dbc(int a, int b);

VecFx32 SteerTowardTarget_020ab1f0(int *entryIndex, SteerObject *object, fx32 scale) {
    SteerDesc *desc = object->desc;
    VecFx32 position = object->position;
    VecFx32 diff;
    VecFx32 result;
    VecFx32 target;
    PartyEntry *entry = GetBoundedEntryField_0206db5c(*entryIndex);
    BOOL hasTarget;
    if (entry->getTarget != NULL) {
        hasTarget = entry->getTarget(entry, &target);
    } else {
        hasTarget = FALSE;
    }
    if (hasTarget && object->time >= desc->homingDelay && desc->turnRate > 0 && !(desc->flags & 0x100)) {
        VEC_Subtract_01ff9e3c(&target, &position, &diff);
        if (VEC_DotProduct_01ff9e6c(&diff, &object->direction) >= -0xa00) {
            VEC_Normalize_01ffaff4(&diff, &diff);
            VEC_Normalize_01ffaff4(&object->direction, &object->direction);
            ScaleVecFx32_01ffafb4(desc->turnRate, &diff, &diff);
            VEC_MultAdd_01ffa09c(0x1000 - desc->turnRate, &object->direction, &diff, &object->direction);
            VEC_Normalize_01ffaff4(&object->direction, &object->direction);
            ScaleVecFx32_01ffafb4(desc->speed, &object->direction, &object->direction);
        }
    }
    ScaleVecFx32_01ffafb4(scale, &object->direction, &result);
    if (desc->flags & 8) {
        fx32 speed = desc->speed - desc->decay * ((func_02023dbc(object->time, 3) * 3) >> 12);
        if (speed <= 0) {
            speed = 0;
        }
        ScaleVecFx32_01ffafb4(speed, &result, &result);
    }
    return result;
}
