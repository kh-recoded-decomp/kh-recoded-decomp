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

extern u8 *ActorRegistry_GetEntityByIndex(u32 actorId);
extern void RebindAnimTracks(void *anim, int blendIndex, int frame);
extern void Flags16_ClearBit1(void *anim);
extern VecFx32 *func_ov001_0207f898(FieldObject *object);
extern u32 SpawnSoundSlot(s32 seqArcId, s32 soundId, VecFx32 *position, u32 flags);
extern u16 FieldObject_GetSavedValue(FieldObject *object);
extern void FieldObject_SetSavedValue(FieldObject *object, u16 value);

void func_ov006_020a0708(FieldObject *object)
{
    object->timer = 0;
    RebindAnimTracks(ActorRegistry_GetEntityByIndex(object->actorId) + 4, object->animBlend, 0);
    Flags16_ClearBit1(ActorRegistry_GetEntityByIndex(object->actorId) + 4);
    if (object->animBlend == 1) {
        SpawnSoundSlot(0x19e, 0, func_ov001_0207f898(object), 0);
        if (!(object->flags & 0x10)) {
            FieldObject_SetSavedValue(object, FieldObject_GetSavedValue(object) | 4);
        }
    }
}
