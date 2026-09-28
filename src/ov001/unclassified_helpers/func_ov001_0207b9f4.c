#include "nitro/types.h"

typedef struct Context {
    u8 pad_000[0x134];
    s32 baseX;
} Context;

typedef struct Point {
    s32 x;
    s32 y;
} Point;

extern Context *data_ov001_020a04cc;
extern int FixedPointMultiply12(int left, int right);
extern void func_ov001_0207ca04(Point *pos, int scale, int arg2, int arg3);

void func_ov001_0207b9f4(int offset, int scale, int arg2, int arg3)
{
    Point pos;

    pos.x = data_ov001_020a04cc->baseX + FixedPointMultiply12(offset, scale);
    pos.y = 0x13000;
    func_ov001_0207ca04(&pos, scale, arg2, arg3);
}
