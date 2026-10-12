#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct ActorEntry ActorEntry;
/* Origin position, target position, and the target-defined range cap. */
extern const VecFx32 *func_ov001_0206dc4c(s32 index);
extern const VecFx32 *func_ov001_0208641c(ActorEntry *entry);
extern fx32 func_ov001_0208643c(ActorEntry *entry);
extern fx32 VEC_Distance(const VecFx32 *a, const VecFx32 *b);
extern void VEC_Subtract(const VecFx32 *a, const VecFx32 *b, VecFx32 *result);
extern void VEC_Normalize(const VecFx32 *source, VecFx32 *result);
extern fx32 VEC_DotProduct(const VecFx32 *a, const VecFx32 *b);
extern s32 GetBiasAdjustedField(s32 index);
extern const s16 gSinFx12Table[];

static inline fx32 Absolute(fx32 value)
{
    return value < 0 ? -value : value;
}

BOOL IsEntryWithinFacingRange(s32 index, ActorEntry *entry, fx32 maximumRange)
{
    const VecFx32 *origin = func_ov001_0206dc4c(index);
    const VecFx32 *target = func_ov001_0208641c(entry);
    fx32 range;
    VecFx32 direction;
    VecFx32 facing;
    s32 angle;
    if (index == 0) {
        range = func_ov001_0208643c(entry);
        if (range > maximumRange) {
            range = maximumRange;
        }
    } else {
        range = maximumRange;
        if (func_ov001_0208643c(entry) <= 0) {
            range = 0;
        }
    }
    if (target == NULL) {
        return FALSE;
    }
    if (Absolute(target->x - origin->x) >= range ||
        Absolute(target->z - origin->z) >= range ||
        Absolute(target->y - origin->y) >= range) {
        return FALSE;
    }
    if (VEC_Distance(target, origin) > range) {
        return FALSE;
    }
    VEC_Subtract(target, origin, &direction);
    direction.y = 0;
    if (direction.x != 0 || direction.y != 0 || direction.z != 0) {
        VEC_Normalize(&direction, &direction);
    }
    facing.x = facing.y = facing.z = 0;
    angle = GetBiasAdjustedField(index) >> 4;
    facing.x = -gSinFx12Table[angle];
    facing.z = -gSinFx12Table[(0x400 - angle) & 0xfff];
    if (index == 0) {
        if (origin->y > target->y) {
            fx32 minZ = target->z - 0x119a;
            fx32 minX = target->x - 0x119a;
            fx32 maxX = target->x + 0x119a;
            fx32 maxZ = target->z + 0x119a;
            if (minX <= origin->x && maxX >= origin->x &&
                minZ <= origin->z && maxZ >= origin->z) {
                return FALSE;
            }
        }
        if (VEC_DotProduct(&facing, &direction) < 0x800) {
            return FALSE;
        }
    }
    return TRUE;
}
