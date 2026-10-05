#include "nitro/types.h"
#include "nitro/fx_types.h"

extern int func_ov042_020bd4bc(void);
extern void func_ov042_020be548(void);
extern void func_ov042_020bd394(int value);
extern void func_ov042_020bd334(fx32 distance);
extern void VEC_Add_01ff9e0c(const VecFx32 *a, const VecFx32 *b, VecFx32 *out);
extern void func_ov042_020bd234(const VecFx32 *pos);
extern void func_ov042_020bd1c0(const VecFx32 *pos);
extern void func_ov042_020bd5e0(fx32 value);
extern void func_ov042_020bd600(int value);
extern void func_ov042_020bd59c(int extent);
extern int func_ov042_020bd0fc(int first, int second);

void SetupMovieCamera_020bb2cc(VecFx32 *focus, int angle, fx32 distance, int extent, BOOL resetSource, int tilt)
{
    VecFx32 goal;
    VecFx32 offset;
    VecFx32 base;
    VecFx32 sum;

    func_ov042_020bd4bc();
    if (resetSource) {
        func_ov042_020be548();
    }
    func_ov042_020bd394(angle);
    func_ov042_020bd334(distance);
    if (focus != NULL) {
        base.x = 0;
        base.y = 0;
        base.z = 0x5000;
        offset = base;
        VEC_Add_01ff9e0c(focus, &offset, &sum);
        goal = sum;
        func_ov042_020bd234(&goal);
        func_ov042_020bd1c0(&goal);
        func_ov042_020bd5e0(goal.y);
    }
    func_ov042_020bd600(tilt);
    func_ov042_020bd59c(extent);
    func_ov042_020bd0fc(1, 0);
}

