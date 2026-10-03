#include "nitro/types.h"

typedef struct LinkedEntry {
    u8 kind;
    u8 flags;
    u16 value;
    struct LinkedEntry *next;
} LinkedEntry;

typedef struct FieldObject {
    u8 pad_00[0x60];
    LinkedEntry *entries;
} FieldObject;

extern void func_ov017_020a5014(FieldObject *object, u16 value, int arg);

void DispatchKind4Entry_020a40ac(FieldObject *object, int arg)
{
    LinkedEntry *entry;

    for (entry = object->entries; entry != NULL; entry = entry->next) {
        if (entry->kind == 4) {
            func_ov017_020a5014(object, entry->value, arg);
            return;
        }
    }
}
