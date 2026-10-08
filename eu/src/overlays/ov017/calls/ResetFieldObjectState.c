#include "nitro/types.h"

typedef struct FieldObject {
    u8 pad_00[0x4a];
    s8 state;
    u8 flags : 7;
    u8 pad_4c[0x24];
    u8 queue[4];
} FieldObject;

extern void ResetFieldObjectToIdle(FieldObject *object);
extern void SetFieldObjectHidden_020a3c98(FieldObject *object, int mode);
extern void AimEntryLandingPoint(void *queue, FieldObject *object);

void ResetFieldObjectState(FieldObject *object)
{
    if ((u8)(s8)(object->state - 1) <= 1) {
        ResetFieldObjectToIdle(object);
    }
    SetFieldObjectHidden_020a3c98(object, 0);
    object->flags &= ~0x20;
    AimEntryLandingPoint(object->queue, object);
}
