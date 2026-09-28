#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct FallingObject
{
    u8 pad_00[0x8];
    void *manager;
    u8 pad_0C[0x34];
    VecFx32 position;
    u8 pad_4C[0x24];
    VecFx32 velocity;
    u8 pad_7C[0x10];
    fx32 unk_8C;
    u8 pad_90[0x8];
    fx32 unk_98;
} FallingObject;

extern void func_ov001_0208502c(void *manager, FallingObject *object);
extern int FixedPointMultiply12(int left, int right);
extern void func_ov001_02085320(FallingObject *object, int mode);
extern void func_ov001_02084f38(FallingObject *object);

int UpdateFallingObject_02085218(FallingObject *object)
{
    func_ov001_0208502c(object->manager, object);
    object->velocity.x = FixedPointMultiply12(object->velocity.x, 0xF33);
    object->velocity.z = FixedPointMultiply12(object->velocity.z, 0xF33);
    object->velocity.y -= 0x7B;
    object->unk_8C -= object->unk_98;
    func_ov001_02085320(object, 0);
    if (object->position.y < -0x14000)
        func_ov001_02084f38(object);
    return 0;
}
