#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct FieldObject {
    u8 pad_00[0x3b];
    u8 lowBits : 4;
    u8 shapeKind : 4;
} FieldObject;

extern const s16 data_0205356c[];
extern VecFx32 *func_ov001_0206dc4c(s32 playerIndex);
extern VecFx32 *func_ov001_0207f870(FieldObject *object);
extern s32 FieldObject_GetClassValue4c_0207f8a8(FieldObject *object);
extern u16 GetBiasAdjustedField_0206dc80(s32 playerIndex);
extern fx32 func_01ffa0f4(const VecFx32 *a, const VecFx32 *b);
extern void VEC_Subtract_01ff9e3c(const VecFx32 *a, const VecFx32 *b, VecFx32 *out);
extern void func_01ff9f88(const VecFx32 *src, VecFx32 *dst);
extern fx32 VEC_DotProduct_01ff9e6c(const VecFx32 *a, const VecFx32 *b);

BOOL IsActorTargetable_0206b4a4(s32 playerIndex, FieldObject *object, s32 range)
{
    VecFx32 *playerPos = func_ov001_0206dc4c(playerIndex);
    VecFx32 *targetPos = func_ov001_0207f870(object);
    fx32 flatDistance = 0x7fffffff;
    fx32 distance;
    int angle;
    VecFx32 direction;
    VecFx32 forward;
    VecFx32 targetFlat;
    VecFx32 playerFlat;

    if (targetPos == NULL) {
        return FALSE;
    }
    distance = func_01ffa0f4(targetPos, playerPos);
    if (distance > FieldObject_GetClassValue4c_0207f8a8(object) || distance > range) {
        return FALSE;
    }
    VEC_Subtract_01ff9e3c(targetPos, playerPos, &direction);
    direction.y = 0;
    if (direction.x != 0 || direction.y != 0 || direction.z != 0) {
        func_01ff9f88(&direction, &direction);
    }
    forward.z = 0;
    forward.y = 0;
    forward.x = 0;
    angle = GetBiasAdjustedField_0206dc80(playerIndex) >> 4;
    forward.x = -data_0205356c[angle];
    forward.z = -data_0205356c[(0x400 - angle) & 0xfff];
    if (object->shapeKind != 1 && object->shapeKind != 8) {
        playerFlat = *playerPos;
        targetFlat = *targetPos;
        targetFlat.y = 0;
        playerFlat.y = 0;
        flatDistance = func_01ffa0f4(&targetFlat, &playerFlat);
    }
    if (VEC_DotProduct_01ff9e6c(&forward, &direction) < 0x800 && flatDistance > 0x1000) {
        return FALSE;
    }
    return TRUE;
}
