
#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct ContactEntry {
    void *object;
    s32 type;
    u8 flags;
} ContactEntry;

typedef struct ContactSet {
    ContactEntry entries[16];
    VecFx32 normals[16];
    u8 entryCount;
    u8 order[32];
    u8 orderCount;
} ContactSet;

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

void ConstrainVectorToContacts_02034d64(VecFx32 *vec, const ContactSet *set)
{
    VecFx32 dir;
    VecFx32 result;
    VecFx32 scaled;
    VecFx32 along;
    VecFx32 unit;
    VecFx32 cross;
    VecFx32 crossCopy;
    fx32 dot;

    switch (set->orderCount) {
    case 0:
        break;
    case 1:
    case 2:
        if (AbsDotProduct_0204a96c(&set->normals[set->order[0]], &set->normals[set->order[1]]) < 0xff0) {
            *vec = data_02053438;
            return;
        } else {
            const VecFx32 *normal = &set->normals[set->order[0]];
            dot = VEC_DotProduct_01ff9e6c(vec, normal);
            scaled = *normal;
            ScaleVecFx32InPlace_0204a5e4(&scaled, dot);
            along = scaled;
            VEC_Subtract_01ff9e3c(vec, &along, &result);
            *vec = result;
        }
        break;
    case 3:
        if (AbsDotProduct_0204a96c(&set->normals[set->order[0]], &set->normals[set->order[1]]) > 0xff0
            || AbsDotProduct_0204a96c(&set->normals[set->order[0]], &set->normals[set->order[2]]) > 0xff0
            || AbsDotProduct_0204a96c(&set->normals[set->order[1]], &set->normals[set->order[2]]) > 0xff0) {
            *vec = data_02053438;
            return;
        } else {
            VecFx32 axis;
            /* Three contacts leave only their shared edge line. */
            VEC_CrossProduct_01ff9ea8(&set->normals[set->order[0]], &set->normals[set->order[1]], &cross);
            crossCopy = cross;
            VEC_NormalizeUnchecked_01ff9f88(&crossCopy, &unit);
            axis = unit;
            dir = *(const VecFx32 *)&unit;
            if (AbsDotProduct_0204a96c(&dir, &set->normals[set->order[2]]) > 0x10) {
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


