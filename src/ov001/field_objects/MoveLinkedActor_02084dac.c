#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct LinkedActorObject {
    u8 pad_00[0x18];
    u8 shape[0x20];
    u8 actorId;
    u8 pad_39[7];
    VecFx32 position;
} LinkedActorObject;

extern void *func_02036240(u32 id);
extern void Obj_SetPosition_0203569c(void *entity, const VecFx32 *position);
extern void func_0203afa0(void *shape, const VecFx32 *position);

void MoveLinkedActor_02084dac(LinkedActorObject *object, const VecFx32 *position)
{
    object->position = *position;
    Obj_SetPosition_0203569c(func_02036240(object->actorId), &object->position);
    func_0203afa0(object->shape, &object->position);
}
