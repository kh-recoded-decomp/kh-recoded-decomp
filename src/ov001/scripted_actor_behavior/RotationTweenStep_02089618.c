#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct RotationTween {
    VecFx32 target;
    VecFx32 from;
    int unk18;
    int duration;
    int remaining;
    int mode;
} RotationTween;

extern fx32 FX_Div_01ff9c84(fx32 numerator, fx32 denominator);
extern void VEC_Subtract_01ff9e3c(const VecFx32 *a, const VecFx32 *b, VecFx32 *out);
extern fx32 FixedPointMultiply12(fx32 a, fx32 b);
extern void func_ov001_02089584(void *matrix, int xAngle, int yAngle, int zAngle);
extern const s16 data_0205356c[];

void *RotationTweenStep_02089618(RotationTween *tween, void *matrix) {
    VecFx32 delta;
    fx32 factor;
    int elapsed;
    int angle;
    int x;
    int y;
    int z;

    factor = 0;
    if (tween->remaining > 0) {
        tween->remaining--;
    }
    if (tween->remaining != 0) {
        elapsed = tween->duration - tween->remaining;
        switch (tween->mode) {
        case 0:
        case 1:
            break;
        case 2:
            factor = FX_Div_01ff9c84(elapsed * 0x1000, tween->duration << 12);
            break;
        case 3:
            angle = elapsed * 0x8000 / tween->duration - 0x4000;
            if (angle < 0) {
                angle += 0x10000;
            }
            factor = (data_0205356c[angle >> 4] + 0x1000) / 2;
            break;
        case 4:
            angle = elapsed * 0x8000 / (tween->duration << 1) - 0x4000;
            if (angle < 0) {
                angle += 0x10000;
            }
            factor = data_0205356c[angle >> 4] + 0x1000;
            break;
        case 5:
            angle = (tween->remaining << 15) / (tween->duration << 1) + 0x4000;
            if (angle < 0) {
                angle += 0x10000;
            }
            factor = data_0205356c[angle >> 4];
            break;
        }
    }
    if (tween->remaining == 0) {
        x = tween->target.x;
        y = tween->target.y;
        z = tween->target.z;
    } else {
        VEC_Subtract_01ff9e3c(&tween->target, &tween->from, &delta);
        x = tween->from.x + FixedPointMultiply12(delta.x, factor);
        y = tween->from.y + FixedPointMultiply12(delta.y, factor);
        z = tween->from.z + FixedPointMultiply12(delta.z, factor);
    }
    func_ov001_02089584(matrix, (u16)x, (u16)y, (u16)z);
    return matrix;
}
