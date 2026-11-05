#include "nitro/types.h"

typedef struct {
    u8 pad_000[0x47];
    s8 mode;
} ObjectState;

BOOL IsFieldObjectPoseNot1(u32 unused1, u32 unused2, ObjectState *obj)
{
    if (obj->mode != 1) {
        return 1;
    }
    return 0;
}
