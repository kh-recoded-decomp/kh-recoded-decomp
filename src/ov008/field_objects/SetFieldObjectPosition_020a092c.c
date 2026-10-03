#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct {
    u8 pad_00[0x38];
    u8 actorId;
    u8 pad_39[0x7];
    VecFx32 position;
} FieldObject;

extern void *func_02036240(u32 actorId);
extern void Obj_SetPosition_0203569c(void *entity, const VecFx32 *position);

void SetFieldObjectPosition_020a092c(FieldObject *object, const VecFx32 *position)
{
    object->position = *position;
    Obj_SetPosition_0203569c(func_02036240(object->actorId), &object->position);
}
