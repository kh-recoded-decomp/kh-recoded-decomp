#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct {
    u8 pad_00[0x30];
    u16 slotFlags;
    u8 actorId;
    u8 pad_33[5];
    VecFx32 position;
    u8 pad_44[0xc];
    u16 flags;
    s8 state;
} Obj;

typedef struct {
    u8 pad_00[8];
    u16 flags;
} RecordSlot;

extern void ClearRecordSlotFlag(int index);
extern void *ActorRegistry_GetEntityByIndex(u32 id);
extern void Obj_SetPosition(void *actor, const VecFx32 *position);
extern RecordSlot *ActorSlot_GetByIndex(int index);
extern void TransitionRecordSlot(int index);
extern void ActorSlot_SetFlag8ByIndex(int index, BOOL enable);

void FieldObject_SetDisabled(Obj *obj, BOOL disable)
{
    if (disable) {
        obj->flags |= 8;
        obj->slotFlags &= ~0x10;
        obj->slotFlags &= ~8;
        obj->flags &= ~0x400;
        ClearRecordSlotFlag(obj->actorId);
    } else {
        obj->flags &= ~8;
        obj->slotFlags |= 0x10;
        obj->slotFlags |= 8;
        Obj_SetPosition(ActorRegistry_GetEntityByIndex(obj->actorId), &obj->position);
        if (!(ActorSlot_GetByIndex(obj->actorId)->flags & 0x100)) {
            TransitionRecordSlot(obj->actorId);
        }
    }
    if (obj->slotFlags & 4) {
        ActorSlot_SetFlag8ByIndex(obj->actorId, (!(obj->flags & 8) && obj->state == 0) ? TRUE : FALSE);
    }
}
