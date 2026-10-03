#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct FieldObject {
    u8 pad_00[0x32];
    u8 actorId;
    u8 pad_33[5];
    VecFx32 position;
} FieldObject;

extern void *func_02036240(u32 actorId);
extern void Obj_SetPosition_0203569c(void *entity, const VecFx32 *position);

void SetFieldObjectPosition_020a40dc(FieldObject *object, const VecFx32 *position)
{
    object->position = *position;
    Obj_SetPosition_0203569c(func_02036240(object->actorId), position);
}
