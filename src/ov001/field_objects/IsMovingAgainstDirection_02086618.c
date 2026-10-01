#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct FieldObject {
    u8 pad_00[0x32];
    u8 actorId;
} FieldObject;

typedef struct ActorBody {
    u8 pad_000[0x150];
    VecFx32 velocity;
} ActorBody;

typedef struct PartyEntry {
    u8 pad_000[0x9c8];
    VecFx32 velocity;
} PartyEntry;

extern PartyEntry *GetBoundedEntryField_0206db5c(int index);
extern ActorBody *func_02036240(u32 actorId);
extern void Vec3MulScalar_0204a680(VecFx32 *v, fx32 factor);
extern void VEC_Add_01ff9e0c(const VecFx32 *a, const VecFx32 *b, VecFx32 *out);
extern void func_01ff9f88(const VecFx32 *src, VecFx32 *dst);
extern fx32 VEC_DotProduct_01ff9e6c(const VecFx32 *a, const VecFx32 *b);

BOOL IsMovingAgainstDirection_02086618(FieldObject *object, int entryIndex, VecFx32 *direction)
{
    BOOL result = FALSE;

    if (direction->y != 0) {
        result = TRUE;
    } else {
        PartyEntry *entry = GetBoundedEntryField_0206db5c(entryIndex);
        VecFx32 velocity = func_02036240(object->actorId)->velocity;
        VecFx32 relative;
        VecFx32 unit;
        VecFx32 normalized;
        fx32 dot = 1;

        Vec3MulScalar_0204a680(&velocity, -1);
        VEC_Add_01ff9e0c(&velocity, &entry->velocity, &relative);
        if (relative.x != 0 || relative.y != 0 || relative.z != 0) {
            func_01ff9f88(&relative, &normalized);
            unit = normalized;
            dot = VEC_DotProduct_01ff9e6c(&unit, direction);
        }
        if (dot < -0x20) {
            result = TRUE;
        }
    }
    return result;
}
