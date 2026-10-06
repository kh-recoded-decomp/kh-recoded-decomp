#include "nitro/types.h"

extern u32 data_ov028_020bb320;
extern s32 Obj_GetWord28(u32 handle);

BOOL func_ov028_020bb080(void)
{
    s32 result = Obj_GetWord28(data_ov028_020bb320);
    return result != 0;
}
