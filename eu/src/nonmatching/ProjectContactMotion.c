/* Pending func_02034d78: outside the build and byte-exact progress. */
#include "src/collision/CollisionContacts.h"

extern fx32 AbsDotProduct(const VecFx32 *, const VecFx32 *);
extern fx32 VEC_DotProduct(const VecFx32 *, const VecFx32 *);
extern void ScaleVecFx32InPlace(VecFx32 *, fx32);
extern void VEC_Subtract(const VecFx32 *, const VecFx32 *, VecFx32 *);
extern void VEC_CrossProduct(const VecFx32 *, const VecFx32 *, VecFx32 *);
extern void VEC_Normalize(const VecFx32 *, VecFx32 *);
extern const VecFx32 gZeroVecFx32;

static inline VecFx32 ScaledVector(VecFx32 value, fx32 scale)
{
    ScaleVecFx32InPlace(&value, scale);
    return value;
}

static inline void SubtractFromMotion(VecFx32 *a, VecFx32 b)
{
    VecFx32 result;
    VEC_Subtract(a, &b, &result);
    *a = result;
}

static inline VecFx32 CrossVectors(const VecFx32 *a, const VecFx32 *b)
{
    VecFx32 result;
    VEC_CrossProduct(a, b, &result);
    return result;
}

static inline VecFx32 NormalizedVector(VecFx32 value)
{
    VecFx32 result;
    VEC_Normalize(&value, &result);
    return result;
}

void ProjectContactMotion(VecFx32 *motion, const CollisionContacts *contacts)
{
    switch (contacts->projectionMode) {
    case 0:
        break;
    case 1:
    case 2: {
        const VecFx32 *normal;
        if (AbsDotProduct(&contacts->normals[contacts->selected[0]],
                &contacts->normals[contacts->selected[1]]) < 0xff0) {
            *motion = gZeroVecFx32;
            return;
        }
        normal = &contacts->normals[contacts->selected[0]];
        SubtractFromMotion(motion, ScaledVector(*normal, VEC_DotProduct(motion, normal)));
        break;
    }
    case 3: {
        if (AbsDotProduct(&contacts->normals[contacts->selected[0]],
                &contacts->normals[contacts->selected[1]]) > 0xff0 ||
            AbsDotProduct(&contacts->normals[contacts->selected[0]],
                &contacts->normals[contacts->selected[2]]) > 0xff0 ||
            AbsDotProduct(&contacts->normals[contacts->selected[1]],
                &contacts->normals[contacts->selected[2]]) > 0xff0) {
            *motion = gZeroVecFx32;
            return;
        }
        VecFx32 projectionAxis = NormalizedVector(CrossVectors(
            &contacts->normals[contacts->selected[0]],
            &contacts->normals[contacts->selected[1]]));
        const VecFx32 axis = projectionAxis;
        if (AbsDotProduct(&axis, &contacts->normals[contacts->selected[2]]) > 0x10) {
            *motion = gZeroVecFx32;
            return;
        }
        *motion = ScaledVector(projectionAxis, VEC_DotProduct(motion, &axis));
        break;
    }
    default:
        *motion = gZeroVecFx32;
    }
}
