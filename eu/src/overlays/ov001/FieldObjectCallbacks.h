#ifndef OV001_FIELD_OBJECT_CALLBACKS_H
#define OV001_FIELD_OBJECT_CALLBACKS_H

#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct FieldObject FieldObject;

typedef struct FieldObjectHitContact {
    fx32 distance;
    VecFx32 direction;
    u32 reserved10[2];
} FieldObjectHitContact;

typedef struct FieldObjectHitMessage {
    VecFx32 direction;
    u8 element;
    u8 reserved0d;
    u16 reserved0e;
    s32 damage;
    s32 unknown14;
    s32 unknown18;
} FieldObjectHitMessage;

typedef struct FieldObjectCallbacks {
    void (*reserved00[10])(void);
    VecFx32 *(*getPosition)(FieldObject *object);
    u32 (*applyHit)(FieldObject *object, const FieldObjectHitMessage *message);
    BOOL (*queryHit)(FieldObject *object, const void *shape,
                     FieldObjectHitContact *contact);
} FieldObjectCallbacks;

/* Partial object view: the intervening fields belong to other subsystems. */
struct FieldObject {
    u32 reserved00;
    FieldObject *next;
    const FieldObjectCallbacks *callbacks;
    u8 reserved0c[0x50 - 0x0c];
    u16 id;
    u8 kind;
};

BOOL IsObjectFlagClear(FieldObject *object);
VecFx32 *FieldObject_GetPosition(FieldObject *object);
BOOL FieldObject_QueryHit(FieldObject *object, const void *shape,
                         FieldObjectHitContact *contact);
u32 FieldObject_ApplyHit(FieldObject *object,
                       const FieldObjectHitMessage *message);

#endif
