#include "nitro/types.h"

#pragma opt_dead_assignments off

typedef struct {
    s32 x;
    s32 y;
} Pos2;

extern u8 *data_ov002_0206c464;
extern s16 data_0205356c[];
extern int func_ov027_020b90a4(void *obj, int index);
extern void func_ov027_020b9360(void *obj, int handle, Pos2 *out, int flag);
extern void func_ov027_020b91c8(void *obj, int handle, Pos2 *pos, int flag);
extern unsigned int func_0202a9d0(unsigned int range);
extern u32 func_02023a98(int value);
extern u32 func_020245e8(u32 a, u32 b);
extern u32 func_02024818(u32 a, u32 b);
extern int func_020241ac(u32 value);

static __inline int CosineWhole(int degrees)
{
    s64 radians = ((s64)degrees * ((s64)0x6488 / 2)) / 0xb4000;
    radians = (radians << 16) / 0x6488;
    return (int)(((s64)data_0205356c[(0x400 - ((int)(radians & 0xffff) >> 4)) & 0xfff] + 0x800) >> 12);
}

void func_ov002_02064d54(void)
{
    Pos2 pos;
    u8 *data;
    int i;
    int handle;
    int row;
    int column;
    int angle;
    int rounded;
    int index;
    s64 radians;

    i = 0;
    *(s16 *)(data_ov002_0206c464 + 0x20) += 8;
    *(s16 *)(data_ov002_0206c464 + 0x20) %= 360;
    do {
        handle = func_ov027_020b90a4(data_ov002_0206c464 + 0x56c, i + 6);
        func_ov027_020b9360(data_ov002_0206c464 + 0x56c, handle, &pos, 0);
        row = pos.y >> 12;
        if (row > 0x5c) {
            pos.y = 0x3c000;
            if (i + 6 > 9) {
                column = func_0202a9d0(0x20) + 8;
            } else {
                column = func_0202a9d0(0x24) + 0xd0;
            }
            pos.x = column << 12;
            func_ov027_020b91c8(data_ov002_0206c464 + 0x56c, handle, &pos, 0);
        } else {
            data = data_ov002_0206c464;
            angle = (i * 90 + *(s16 *)(data + 0x20)) % 360;
            if (angle > 0) {
                rounded = func_020241ac(func_020245e8(0x3f000000, func_02023a98(angle << 12)));
            } else {
                rounded = func_020241ac(func_02024818(func_02023a98(angle << 12), 0x3f000000));
            }
            radians = ((s64)rounded * ((s64)0x6488 / 2)) / 0xb4000;
            radians = (radians << 16) / 0x6488;
            index = (0x400 - ((int)(radians & 0xffff) >> 4)) & 0xfff;
            pos.y = (row + 1) << 12;
            pos.x = ((int)(((s64)data_0205356c[index] + 0x800) >> 12) + (pos.x >> 12)) << 12;
            func_ov027_020b91c8(data + 0x56c, handle, &pos, 0);
        }
        i++;
    } while (i < 8);
}
