#include "nitro/types.h"

typedef struct FieldObject {
    u8 pad_00[0x33];
    u8 slotIndex;
    u8 pad_34[0xBD - 0x34];
    u8 flagsLow : 4;
    u8 stateLevel : 4;
} FieldObject;

typedef struct SlotRecord {
    u32 low : 9;
    u32 slotIndex : 9;
} SlotRecord;

extern SlotRecord *func_ov032_020bbc60(FieldObject *object);
extern int DispatchActorCollision_020a5130(FieldObject *object, void *other, void *context);

int DispatchCollisionUnlessSameSlot_020a52b8(FieldObject *object, void *other, void *context)
{
    if (object->stateLevel >= 5 && object->slotIndex == func_ov032_020bbc60(object)->slotIndex) {
        return 0;
    }
    return DispatchActorCollision_020a5130(object, other, context);
}
