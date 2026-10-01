#include "nitro/types.h"

typedef struct {
    u8 pad_00[0x58];
    u8 body[0x15];
    u8 disabled : 1;
} FlaggedObject;

void *func_ov006_020a0bec(FlaggedObject *object)
{
    if (object->disabled) {
        return NULL;
    }
    return object->body;
}
