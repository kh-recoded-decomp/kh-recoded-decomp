#include "src/overlays/ov001/FieldObjectCallbacks.h"

extern u32 ReadSessionPackedBits(u16 id, u8 kind);

BOOL IsObjectFlagClear(FieldObject *object)
{
    return (ReadSessionPackedBits(object->id, object->kind) & 1) == 0;
}
