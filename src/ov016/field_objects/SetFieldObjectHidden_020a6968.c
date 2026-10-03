#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct {
    u8 pad_00[0x30];
    u16 attributes;
    u8 actorId;
    u8 pad_33[0x38 - 0x33];
    VecFx32 position;
    u8 pad_44[0xbe - 0x44];
    u8 unk_BE_low : 4;
    u8 state : 4;
    u8 pad_bf;
    u32 flags;
} FieldObject;

extern void *func_02036240(u32 actorId);
extern void Obj_SetPosition_0203569c(void *entity, const VecFx32 *position);
extern void func_ov016_020a2668(FieldObject *obj, int enabled);
extern BOOL func_ov016_020a69f0(FieldObject *obj);
extern void ActorSlot_SetFlag8ByIndex_02036120(int index, BOOL enable);

void SetFieldObjectHidden_020a6968(FieldObject *obj, BOOL hidden)
{
    BOOL enable;
    BOOL blocked;

    if (hidden) {
        obj->flags |= 0x10;
        func_ov016_020a2668(obj, 0);
    } else {
        obj->flags &= ~0x10;
        Obj_SetPosition_0203569c(func_02036240(obj->actorId), &obj->position);
        func_ov016_020a2668(obj, 1);
    }
    if (obj->attributes & 4) {
        enable = FALSE;
        if (!func_ov016_020a69f0(obj)) {
            blocked = TRUE;
            if (obj->state <= 3 && ((1 << obj->state) & 0xb)) {
                blocked = FALSE;
            }
            if (!blocked) {
                enable = TRUE;
            }
        }
        ActorSlot_SetFlag8ByIndex_02036120(obj->actorId, enable);
    }
}
