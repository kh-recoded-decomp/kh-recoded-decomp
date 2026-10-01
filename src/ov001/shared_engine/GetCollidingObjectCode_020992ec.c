#include "nitro/types.h"

typedef struct FieldObject {
    u8 pad_000[0x1d8];
    u8 unk_1D8;
} FieldObject;

extern u8 *g_stageManager_020a0508;
extern FieldObject *func_ov001_0206dcac(const void *bounds, void *hitInfo);

u16 GetCollidingObjectCode_020992ec(const void *bounds, void *hitInfo)
{
    FieldObject *object;

    if (g_stageManager_020a0508 == NULL) {
        return 0;
    }
    object = func_ov001_0206dcac(bounds, hitInfo);
    if (object == NULL) {
        return 0;
    }
    return object->unk_1D8 + 1;
}
