#include "nitro/types.h"

extern void func_ov001_02079790(s32 obj, u32 flag);

void func_ov001_02079f70(s32 obj)
{
    func_ov001_02079790(obj, 0);
    *(u32 *)(obj + 8) = 6;
}
