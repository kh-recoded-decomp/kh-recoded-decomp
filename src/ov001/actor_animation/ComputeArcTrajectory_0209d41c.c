#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct ArcTrajectory {
    VecFx32 position;
    VecFx32 velocity;
    fx32 unk18;
    fx32 gravity;
} ArcTrajectory;

extern fx32 FixedPointMultiply12(fx32 left, fx32 right);
extern fx32 func_01ff9cfc(fx32 value);
extern fx32 FX_Div_01ff9c84(fx32 numer, fx32 denom);
extern fx32 func_01ffaff4(const VecFx32 *src, VecFx32 *dst);
extern void VEC_MultAdd_01ffa09c(fx32 scale, const VecFx32 *v, const VecFx32 *add, VecFx32 *dst);

void ComputeArcTrajectory_0209d41c(ArcTrajectory *arc, const VecFx32 *start, const VecFx32 *target, fx32 height, fx32 duration)
{
    VecFx32 direction;
    VecFx32 apex;
    fx32 distance;
    fx32 apexDistance;
    fx32 speed;
    fx32 ratio;
    fx32 dx;
    fx32 dz;
    fx32 apexTime;
    fx32 velocityY;
    fx32 peakY;
    fx32 gravity;

    peakY = start->y + height;
    dx = target->x - start->x;
    dz = target->z - start->z;
    distance = func_01ff9cfc(FixedPointMultiply12(dx, dx) + FixedPointMultiply12(dz, dz));
    if (distance < 0x80) {
        distance = 0x80;
    }
    ratio = func_01ff9cfc(FX_Div_01ff9c84(start->y - peakY, target->y - peakY));
    apexDistance = FixedPointMultiply12(ratio, distance);
    if (0x1000 - ratio == 0) {
        apexDistance = 0;
    } else {
        apexDistance = FX_Div_01ff9c84(-apexDistance, 0x1000 - ratio);
    }
    if (apexDistance <= 0 || apexDistance >= distance) {
        apexDistance = FixedPointMultiply12(ratio, distance);
        if (ratio + 0x1000 == 0) {
            apexDistance = 0;
        } else {
            apexDistance = FX_Div_01ff9c84(apexDistance, ratio + 0x1000);
        }
        if (apexDistance <= 0 || apexDistance >= distance) {
            apexDistance = 0;
        }
    }
    direction.x = dx;
    gravity = 0;
    direction.y = 0;
    direction.z = dz;
    func_01ffaff4(&direction, &direction);
    VEC_MultAdd_01ffa09c(apexDistance, &direction, start, &apex);
    apex.y = peakY;
    apexTime = FixedPointMultiply12(duration, FX_Div_01ff9c84(apexDistance, distance));
    {
        fx32 rise = (start->y - apex.y) * 2;
        fx32 timeSquared = FixedPointMultiply12(apexTime, apexTime);

        if (timeSquared != 0) {
            gravity = FX_Div_01ff9c84(rise, timeSquared);
        }
    }
    velocityY = FixedPointMultiply12(-gravity, apexTime);
    if (duration == 0) {
        speed = 0;
    } else {
        speed = FX_Div_01ff9c84(distance, duration);
    }
    arc->velocity.x = FixedPointMultiply12(speed, direction.x);
    arc->velocity.z = FixedPointMultiply12(speed, direction.z);
    arc->velocity.y = velocityY;
    arc->gravity = gravity;
    arc->position = *start;
}
