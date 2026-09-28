#include "nitro/types.h"

extern u32 g_handle_020bb300;
extern s32 func_0202a78c(u32 handle);

BOOL func_ov028_020bb060(void)
{
    s32 result = func_0202a78c(g_handle_020bb300);
    return result != 0;
}
