#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct FallingObject {
    u8 pad_00[8];
    void *manager;
    u8 pad_0C[0x60];
    fx32 maxDistance;
    VecFx32 position;
    VecFx32 velocity;
    u8 pad_88[4];
    fx32 height;
    u8 pad_90[8];
    fx32 fallStep;
} FallingObject;

extern void func_ov001_0208502c(void *manager, FallingObject *object);
extern void VEC_MultAdd_01ffa09c(fx32 scale, const VecFx32 *v, const VecFx32 *add, VecFx32 *dst);
extern BOOL ClampVecLength_0204ac28(VecFx32 *vec, fx32 maxLength);
extern fx32 VEC_Mag_01ff9f28(const VecFx32 *v);
extern fx32 FX_Div_01ff9c84(fx32 numer, fx32 denom);
extern int FixedPointMultiply12(int left, int right);
extern void func_ov001_02085320(FallingObject *object, int mode);

int StepFallingObject_020850bc(FallingObject *object)
{
    VecFx32 next;

    func_ov001_0208502c(object->manager, object);
    VEC_MultAdd_01ffa09c(0x14, &object->velocity, &object->position, &next);
    object->position = next;
    object->position.y -= 0x52;
    ClampVecLength_0204ac28(&object->position, object->maxDistance);
    object->fallStep = FixedPointMultiply12(0x6488, FX_Div_01ff9c84(VEC_Mag_01ff9f28(&object->position), 0x82b2));
    object->height -= object->fallStep;
    func_ov001_02085320(object, 1);
    return 0;
}
