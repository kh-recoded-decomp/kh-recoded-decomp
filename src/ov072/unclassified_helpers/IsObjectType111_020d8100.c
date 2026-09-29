#include "nitro/types.h"

typedef struct {
    s32 typeId;
} ObjectHeader;

BOOL IsObjectType111_020d8100(ObjectHeader *object)
{
    if (object->typeId == 0x111) {
        return TRUE;
    }
    return FALSE;
}
