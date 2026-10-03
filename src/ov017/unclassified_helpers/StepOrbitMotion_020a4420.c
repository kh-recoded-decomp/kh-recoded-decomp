#include "nitro/types.h"
#include "nitro/fx_types.h"
#include "nitro/fx.h"

typedef struct OrbitPath {
    int easing;
    VecFx32 offset;
    VecFx32 axis;
    fx32 radius;
    fx32 duration;
    fx32 angle;
} OrbitPath;

typedef struct OrbitState {
    fx32 time;
    VecFx32 center;
} OrbitState;

typedef struct OrbitObject {
    u8 pad_00[0x38];
    VecFx32 position;
    u8 pad_44[8];
    fx32 overflow;
} OrbitObject;

extern OrbitPath *GetPool2Entry_020a41d4(OrbitObject *owner, int index);
extern fx32 func_0204a174(fx32 time, fx32 duration, int easing);
extern void NegateVecFx32_0204aa40(VecFx32 *vec);
extern void ScaleVecFx32InPlace_0204a5e4(VecFx32 *vec, fx32 scale);
extern fx32 func_02006450(fx32 left, fx32 right);
extern void RotateVectorAroundAxis_0204b34c(VecFx32 *vec, const VecFx32 *axis, s32 angle);
extern void VEC_Add_01ff9e0c(const VecFx32 *a, const VecFx32 *b, VecFx32 *out);

static inline VecFx32 Negated(VecFx32 vec)
{
    NegateVecFx32_0204aa40(&vec);
    return vec;
}

static inline VecFx32 Scaled(VecFx32 vec, fx32 scale)
{
    ScaleVecFx32InPlace_0204a5e4(&vec, scale);
    return vec;
}

BOOL StepOrbitMotion_020a4420(OrbitState *state, OrbitObject *object, int index)
{
    OrbitPath *path = GetPool2Entry_020a41d4(object, index);
    fx32 progress = FX32_ONE;

    state->time += object->overflow + FX32_ONE;
    object->overflow = 0;
    if (state->time >= path->duration) {
        object->overflow = state->time - path->duration;
    } else {
        progress = func_0204a174(state->time, path->duration, path->easing);
    }
    object->position = Scaled(Negated(path->offset), path->radius);
    RotateVectorAroundAxis_0204b34c(&object->position, &path->axis, func_02006450(path->angle, progress));
    VEC_Add_01ff9e0c(&object->position, &state->center, &object->position);
    if (state->time >= path->duration) {
        return TRUE;
    }
    return FALSE;
}
