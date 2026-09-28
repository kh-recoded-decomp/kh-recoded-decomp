#include "nitro/types.h"
#include "nitro/fx.h"

typedef struct SceneObject {
    u8 pad_00[0x40];
    VecFx32 position;
} SceneObject;

extern fx32 func_01ffa0f4(const VecFx32 *a, const VecFx32 *b);

BOOL SceneObject_IsPointWithinOneUnit_02081a88(SceneObject *object, const VecFx32 *point)
{
    if (func_01ffa0f4(point, &object->position) < FX32_ONE) {
        return TRUE;
    }
    return FALSE;
}
