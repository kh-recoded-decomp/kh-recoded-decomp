#include "nitro/types.h"

typedef struct ObjectClass {
    u8 pad_00[0x8];
    u16 flags;
} ObjectClass;

typedef struct FieldObject {
    u8 pad_00[0xc];
    ObjectClass *objectClass;
    u8 pad_10[0x28];
    u8 actorId;
    u8 pad_39[0x1f];
    s32 active;
} FieldObject;

extern void func_ov011_020a06e8(FieldObject *object, int state);
extern BOOL func_02036810(int actorId);
extern void *func_02036240(int actorId);
extern void SetObjectAnimTrack_0207f8d0(FieldObject *object, s8 track);
extern void ActorSlot_SetFlag8ByIndex_02036120(int index, BOOL enable);
extern void func_02036924(int index);
extern void FieldObject_SetEnabled_0207f6f4(FieldObject *object, BOOL enabled);

void FieldObject_ResetToIdle_020a10c4(FieldObject *object)
{
    if (object->active != 0) {
        func_ov011_020a06e8(object, 0);
        if (func_02036810(object->actorId)) {
            func_02036240(object->actorId);
            SetObjectAnimTrack_0207f8d0(object, 0);
            ActorSlot_SetFlag8ByIndex_02036120(object->actorId, TRUE);
            if ((object->objectClass->flags & 0x100) == 0) {
                func_02036924(object->actorId);
            }
        }
        FieldObject_SetEnabled_0207f6f4(object, TRUE);
    }
}
