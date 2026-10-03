#include "nitro/types.h"

struct FieldObject;

typedef struct FieldDef {
    u8 pad_00[0x30];
    BOOL (*isBusy)(struct FieldObject *object);
    u8 pad_34[0xa];
    u16 objectCount;
} FieldDef;

typedef struct LinkedEntry {
    u8 kind;
} LinkedEntry;

typedef struct FieldObject {
    u8 pad_00[4];
    FieldDef *def;
    u8 pad_08[0x58];
    LinkedEntry *entries;
} FieldObject;

extern FieldObject *func_ov001_0208635c(FieldDef *owner, int index);

FieldObject *FindBusyKind4Object_020a4b68(FieldObject *self)
{
    int i = 0;
    int count = self->def->objectCount;
    FieldObject *object;
    BOOL busy;

    for (; i < count; i++) {
        object = func_ov001_0208635c(self->def, i);
        if (object != NULL && object != self && object->entries != NULL && object->entries->kind == 4) {
            if (object->def->isBusy != NULL) {
                busy = object->def->isBusy(object);
            } else {
                busy = FALSE;
            }
            if (busy) {
                return object;
            }
        }
    }
    return NULL;
}
