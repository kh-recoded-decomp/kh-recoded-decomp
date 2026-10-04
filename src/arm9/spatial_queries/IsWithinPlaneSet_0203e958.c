#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct ShapeData {
    VecFx32 center;
    VecFx32 halfExtent;
    u8 pad_18[0x24];
    u8 isOriented : 1;
} ShapeData;

typedef struct CollisionShape {
    ShapeData *data;
    s32 bounds[6];
    s32 kind;
} CollisionShape;

extern VecFx32 *func_ov021_020af5b4(void);
extern VecFx32 *func_ov021_020af6fc(void);
extern VecFx32 GetShapeCenter_0203b43c(const CollisionShape *shape);
extern void VEC_Subtract_01ff9e3c(const VecFx32 *a, const VecFx32 *b, VecFx32 *out);
extern fx32 VEC_DotProduct_01ff9e6c(const VecFx32 *a, const VecFx32 *b);
extern int abs_0203b430(int value);
extern void func_0204abf4(VecFx32 *vec, int (*transform)(int));
extern fx32 func_0203b2cc(const CollisionShape *shape, const VecFx32 *normal);

static inline VecFx32 SubtractVec(const VecFx32 *a, const VecFx32 *b)
{
    VecFx32 result;
    VEC_Subtract_01ff9e3c(a, b, &result);
    return result;
}

static inline VecFx32 AbsVec(VecFx32 vec)
{
    func_0204abf4(&vec, abs_0203b430);
    return vec;
}

BOOL IsWithinPlaneSet_0203e958(const CollisionShape *shape, fx32 margin)
{
    VecFx32 *origin = func_ov021_020af5b4();
    VecFx32 relative;
    VecFx32 center = GetShapeCenter_0203b43c(shape);
    VecFx32 *normals;
    u8 i;

    relative = SubtractVec(&center, origin);
    normals = func_ov021_020af6fc();
    if (shape->kind == 1 && shape->data->isOriented) {
        for (i = 0; i < 4; i++) {
            VecFx32 absNormal = AbsVec(normals[i]);
            fx32 radius = VEC_DotProduct_01ff9e6c(&absNormal, &shape->data->halfExtent);
            if (VEC_DotProduct_01ff9e6c(&normals[i], &relative) > radius + margin) {
                return FALSE;
            }
        }
    } else {
        for (i = 0; i < 4; i++) {
            fx32 radius = func_0203b2cc(shape, &normals[i]);
            if (VEC_DotProduct_01ff9e6c(&normals[i], &relative) > radius + margin) {
                return FALSE;
            }
        }
    }
    return TRUE;
}
