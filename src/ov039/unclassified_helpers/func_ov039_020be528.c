#include "nitro/types.h"

extern void func_ov039_020bcd04(int *obj, u32 flags, u32 style);
extern void func_020015a0(int *obj, int x, int y, int z, u32 color, u32 style);
extern void Obj_SetField14_02001490(int *obj, int value);

void func_ov039_020be528(int *obj, int x, int y, int z, u32 color, u32 style, u32 flags)
{
    int saved = *obj;

    func_ov039_020bcd04(obj, flags, style);
    func_020015a0(obj, x + 1, y + 1, z + 1, color, style);
    func_020015a0(obj, x, y, z, color, style);
    Obj_SetField14_02001490(obj, saved);
}
