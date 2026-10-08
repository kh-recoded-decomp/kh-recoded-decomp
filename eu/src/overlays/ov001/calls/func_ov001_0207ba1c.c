#include "nitro/types.h"

typedef struct Context {
    u8 pad_000[0x134];
    s32 baseX;
} Context;

typedef struct Point {
    s32 x;
    s32 y;
} Point;

extern Context *data_ov001_020a04ec;
extern int FX_Mul(int left, int right);
extern void DrawScaledTextureQuad(Point *pos, int scale, int arg2, int arg3);

void func_ov001_0207ba1c(int offset, int scale, int arg2, int arg3)
{
    Point pos;

    pos.x = data_ov001_020a04ec->baseX + FX_Mul(offset, scale);
    pos.y = 0x13000;
    DrawScaledTextureQuad(&pos, scale, arg2, arg3);
}
