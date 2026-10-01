#include "nitro/types.h"

typedef struct ActorRecord {
    u8 pad_00[6];
    s16 slotValues[5];
    u8 pad_10[0xdc - 0x10];
    s16 slotCounts[5];
} ActorRecord;

typedef struct FieldObject FieldObject;

typedef struct FieldObjectOps {
    u8 pad_00[0xc];
    void (*onRefresh)(FieldObject *object);
} FieldObjectOps;

struct FieldObject {
    u32 unk_00;
    FieldObjectOps *ops;
    u8 pad_08[0x28];
    u16 flags;
    u8 actorId;
    u8 pad_33[0x14];
    s8 slotValue;
};

extern ActorRecord *func_02036240(u32 id);

void FieldObject_ApplyActorSlotIndex_02086384(FieldObject *object)
{
    FieldObjectOps *ops = object->ops;

    if (object->flags & 4) {
        ActorRecord *actor = func_02036240(object->actorId);
        int i;

        for (i = 0; i < 5; i++) {
            if (actor->slotCounts[(u16)i] > 0) {
                object->slotValue = actor->slotValues[(u16)i];
                break;
            }
        }
        if (ops->onRefresh != NULL) {
            ops->onRefresh(object);
        }
    }
}
