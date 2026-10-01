#include "nitro/types.h"

typedef struct {
    u8 pad_00[0x94];
    s8 filledSlots;
} SlotOwner;

typedef struct {
    u8 pad_00[0x08];
    SlotOwner *owner;
    u8 pad_0c[0x42];
    u16 flags;
    u8 pad_50[0x03];
    s8 state;
    u8 pad_54[0x18];
    s8 cooldown;
    u8 disabled : 1;
    s8 remaining;
    s8 usedCount;
} FieldObject;

extern BOOL func_ov006_020a0754(FieldObject *object, void *query);
extern u16 FieldObject_GetSavedValue_0207f9a8(FieldObject *object);
extern void FieldObject_SetSavedValue_0207f9c8(FieldObject *object, u16 value);
extern void func_ov006_020a06e8(FieldObject *object);

int func_ov006_020a0a3c(FieldObject *object, void *query)
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
    if (!func_ov006_020a0754(object, query)) {
        return 0x10;
    }
    if (!(FieldObject_GetSavedValue_0207f9a8(object) & 1)) {
        FieldObject_SetSavedValue_0207f9c8(object, FieldObject_GetSavedValue_0207f9a8(object) | 1);
    }
    owner->filledSlots++;
    object->remaining--;
    object->usedCount++;
    if (object->remaining == 0) {
        object->flags &= ~0x10;
    }
    if (object->state == 0) {
        object->state = 1;
        func_ov006_020a06e8(object);
    }
    object->cooldown = 15;
    return 0;
}
