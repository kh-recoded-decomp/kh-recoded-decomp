#include "nitro/types.h"

extern u8 data_02057b24;
extern void func_0200b494(u32 param1, void *table, s32 start, s32 end, u32 limit);

void func_0200d530(u32 param1, s32 start, s32 length)
{
    func_0200b494(param1, &data_02057b24, start, start + length, 0xffff);
}
