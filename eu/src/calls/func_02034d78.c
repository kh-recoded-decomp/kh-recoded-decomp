#define AbsDotProduct_0204a96c AbsDotProduct
#define ScaleVecFx32InPlace_0204a5e4 ScaleVecFx32InPlace
#define VEC_CrossProduct_01ff9ea8 VEC_CrossProduct
#define VEC_DotProduct_01ff9e6c VEC_DotProduct
#define VEC_NormalizeUnchecked_01ff9f88 VEC_Normalize
#define VEC_Subtract_01ff9e3c VEC_Subtract
#define data_02053438 gZeroVecFx32
#include "src/collision/CollisionContacts.h"

extern const VecFx32 data_02053438;
extern fx32 AbsDotProduct_0204a96c(const VecFx32 *a, const VecFx32 *b);
extern fx32 VEC_DotProduct_01ff9e6c(const VecFx32 *a, const VecFx32 *b);
extern void VEC_Subtract_01ff9e3c(const VecFx32 *a, const VecFx32 *b, VecFx32 *out);
extern void VEC_CrossProduct_01ff9ea8(const VecFx32 *a, const VecFx32 *b, VecFx32 *out);
extern void VEC_NormalizeUnchecked_01ff9f88(const VecFx32 *src, VecFx32 *dst);
extern void ScaleVecFx32InPlace_0204a5e4(VecFx32 *vec, fx32 scale);

static inline VecFx32 VecScaled(VecFx32 v, fx32 scale)
{
    ScaleVecFx32InPlace_0204a5e4(&v, scale);
    return v;
}

void func_02034d78(VecFx32 *vec, const CollisionContacts *set)
{
    VecFx32 dir;
    VecFx32 result;
    VecFx32 scaled;
    VecFx32 along;
    VecFx32 unit;
    VecFx32 cross;
    VecFx32 crossCopy;
    fx32 dot;

    switch (set->projectionMode) {
    case 0:
        break;
    case 1:
    case 2:
        if (AbsDotProduct_0204a96c(&set->normals[set->selected[0]], &set->normals[set->selected[1]]) < 0xff0) {
            *vec = data_02053438;
            return;
        } else {
            const VecFx32 *normal = &set->normals[set->selected[0]];
            dot = VEC_DotProduct_01ff9e6c(vec, normal);
            scaled = *normal;
            ScaleVecFx32InPlace_0204a5e4(&scaled, dot);
            along = scaled;
            VEC_Subtract_01ff9e3c(vec, &along, &result);
            *vec = result;
        }
        break;
    case 3:
        if (AbsDotProduct_0204a96c(&set->normals[set->selected[0]], &set->normals[set->selected[1]]) > 0xff0
            || AbsDotProduct_0204a96c(&set->normals[set->selected[0]], &set->normals[set->selected[2]]) > 0xff0
            || AbsDotProduct_0204a96c(&set->normals[set->selected[1]], &set->normals[set->selected[2]]) > 0xff0) {
            *vec = data_02053438;
            return;
        } else {
            VecFx32 axis;
            /* Try the first two selected normals' crease; the third can block it. */
            VEC_CrossProduct_01ff9ea8(&set->normals[set->selected[0]], &set->normals[set->selected[1]], &cross);
            crossCopy = cross;
            VEC_NormalizeUnchecked_01ff9f88(&crossCopy, &unit);
            axis = unit;
            dir = *(const VecFx32 *)&unit;
            if (AbsDotProduct_0204a96c(&dir, &set->normals[set->selected[2]]) > 0x10) {
                *vec = data_02053438;
                return;
            }
            *vec = VecScaled(axis, VEC_DotProduct_01ff9e6c(vec, &dir));
        }
        break;
    default:
        *vec = data_02053438;
        break;
    }
}
