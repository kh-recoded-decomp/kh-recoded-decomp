#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct {
    u8 pad_00[0x38];
    u8 actorId;
    u8 pad_39[0x15];
    u16 flags;
    u8 pad_50[0x03];
    s8 animBlend;
    u8 pad_54[0x14];
    s32 timer;
} FieldObject;

extern u8 *func_02036240(u32 actorId);
extern void RebindAnimTracks_020809d0(void *anim, int blendIndex, int frame);
extern void func_0202f4e8(void *anim);
extern VecFx32 *func_ov001_0207f870(FieldObject *object);
extern u32 func_0204da8c(s32 seqArcId, s32 soundId, VecFx32 *position, u32 flags);
extern u16 FieldObject_GetSavedValue_0207f9a8(FieldObject *object);
extern void FieldObject_SetSavedValue_0207f9c8(FieldObject *object, u16 value);

void func_ov006_020a06e8(FieldObject *object)
{
    object->timer = 0;
    RebindAnimTracks_020809d0(func_02036240(object->actorId) + 4, object->animBlend, 0);
    func_0202f4e8(func_02036240(object->actorId) + 4);
    if (object->animBlend == 1) {
        func_0204da8c(0x19e, 0, func_ov001_0207f870(object), 0);
        if (!(object->flags & 0x10)) {
            FieldObject_SetSavedValue_0207f9c8(object, FieldObject_GetSavedValue_0207f9a8(object) | 4);
        }
    }
}
