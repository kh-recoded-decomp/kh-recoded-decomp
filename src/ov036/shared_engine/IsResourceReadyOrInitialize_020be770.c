#include "nitro/types.h"

typedef struct Resource {
    u8 pad_000[0x628];
    s32 ready;
} Resource;

extern int func_0204d6fc(void);

BOOL IsResourceReadyOrInitialize_020be770(Resource *resource)
{
    if (resource->ready != 0) {
        return TRUE;
    }
    if (func_0204d6fc() == 0) {
        return TRUE;
    }
    return FALSE;
}
