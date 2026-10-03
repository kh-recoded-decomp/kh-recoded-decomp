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

extern void func_02036974(int index);
extern void *func_02036240(u32 id);
extern void Obj_SetPosition_0203569c(void *actor, const VecFx32 *position);
extern RecordSlot *func_02036810(int index);
extern void func_02036924(int index);
extern void ActorSlot_SetFlag8ByIndex_02036120(int index, BOOL enable);

void FieldObject_SetDisabled_020a333c(Obj *obj, BOOL disable)
{
    if (disable) {
        obj->flags |= 8;
        obj->slotFlags &= ~0x10;
        obj->slotFlags &= ~8;
        obj->flags &= ~0x400;
        func_02036974(obj->actorId);
    } else {
        obj->flags &= ~8;
        obj->slotFlags |= 0x10;
        obj->slotFlags |= 8;
        Obj_SetPosition_0203569c(func_02036240(obj->actorId), &obj->position);
        if (!(func_02036810(obj->actorId)->flags & 0x100)) {
            func_02036924(obj->actorId);
        }
    }
    if (obj->slotFlags & 4) {
        ActorSlot_SetFlag8ByIndex_02036120(obj->actorId, (!(obj->flags & 8) && obj->state == 0) ? TRUE : FALSE);
    }
}
