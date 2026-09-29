#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct WorldObject {
    u8 pad_00[0x8];
    u16 flags;
    u8 pad_0A[0xb8 - 0xa];
    VecFx32 position;
    u8 pad_C4[0x11c - 0xc4];
    u8 shape[0x1a8 - 0x11c];
    u8 probe[0x18];
} WorldObject;

extern fx32 func_02034c24(void *shape);
extern BOOL func_02036b44(void *sphere, const VecFx32 *center, fx32 radius, int useLocal);

void SetObjectProbeSphere_020361b8(WorldObject *object, BOOL enable, fx32 radius)
{
    if (enable) {
        if (radius == 0) {
            radius = (fx32)(((s64)func_02034c24(object->shape) * 0x1800 + 0x800) >> 12);
        }
        func_02036b44(object->probe, &object->position, radius, 0);
        object->flags |= 0x10;
    } else {
        object->flags &= ~0x10;
    }
}
