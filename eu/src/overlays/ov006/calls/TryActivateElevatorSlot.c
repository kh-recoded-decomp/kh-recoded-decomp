#include "nitro/types.h"

typedef struct SlotOwner {
    u8 pad_00[0x94];
    s8 filledSlots;
} SlotOwner;

typedef struct FieldObject {
    u8 pad_00[8];
    SlotOwner *owner;
    u8 pad_0c[0x42];
    u16 flags;
    u8 pad_50[3];
    s8 state;
    u8 pad_54[0x18];
    s8 cooldown;
    u8 disabled : 1;
    s8 remaining;
    s8 usedCount;
} FieldObject;

extern BOOL IsPlayerInFacingHalfPlane(FieldObject *object, void *query);
extern u16 FieldObject_GetSavedValue(FieldObject *object);
extern void FieldObject_SetSavedValue(FieldObject *object, u16 value);
extern void func_ov006_020a0708(FieldObject *object);

int TryActivateElevatorSlot(FieldObject *object, void *query)
{
    SlotOwner *owner = object->owner;

    if (object->disabled) {
        return 0x10;
    }
    if (owner->filledSlots >= 12 || object->remaining == 0) {
        return 0x10;
    }
    if (object->cooldown > 0 || object->state >= 2) {
        return 0x10;
    }
    if (!IsPlayerInFacingHalfPlane(object, query)) {
        return 0x10;
    }
    if (!(FieldObject_GetSavedValue(object) & 1)) {
        FieldObject_SetSavedValue(
            object,
            FieldObject_GetSavedValue(object) | 1
        );
    }
    owner->filledSlots++;
    object->remaining--;
    object->usedCount++;
    if (object->remaining == 0) {
        object->flags &= ~0x10;
    }
    if (object->state == 0) {
        object->state = 1;
        func_ov006_020a0708(object);
    }
    object->cooldown = 15;
    return 0;
}
