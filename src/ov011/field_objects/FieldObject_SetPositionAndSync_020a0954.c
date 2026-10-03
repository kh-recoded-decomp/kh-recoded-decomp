#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct FieldObject {
    u8 pad_00[0x38];
    u8 actorId;
    u8 pad_39[7];
    VecFx32 position;
} FieldObject;

extern BOOL func_02036810(int actorId);
extern void *func_02036240(int actorId);
extern void Obj_SetPosition_0203569c(void *entity, const VecFx32 *position);

void FieldObject_SetPositionAndSync_020a0954(FieldObject *object, const VecFx32 *position)
{
    object->position = *position;
    if (func_02036810(object->actorId)) {
        Obj_SetPosition_0203569c(func_02036240(object->actorId), &object->position);
    }
}
