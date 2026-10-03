#include "nitro/types.h"

typedef struct CameraSwing {
    s32 unk00;
    s32 duration;
    s32 angle;
    s32 speed;
    s32 accel;
    s32 spin;
} CameraSwing;

extern u32 random_next_scaled_0202aa04(u32 upperBound);

void InitSpinCameraOrbit_020c3500(CameraSwing *swing)
{
    s32 sign;
    swing->angle = random_next_scaled_0202aa04(0x168000);
    swing->speed = 0x1ec;
    swing->accel = 0x333;
    sign = random_next_scaled_0202aa04(2) != 0 ? 1 : -1;
    swing->spin = sign * 0xf000;
    swing->duration = 0xa000;
}
