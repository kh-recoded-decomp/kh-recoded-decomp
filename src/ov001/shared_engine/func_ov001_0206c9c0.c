#include "nitro/types.h"

extern u32 func_0202a178(u32 size);
extern void func_ov001_0206c924(void);

extern u32 g_obj_020a0498;

void func_ov001_0206c9c0(void)
{
    if (g_obj_020a0498 == 0) {
        g_obj_020a0498 = func_0202a178(0xa4);
        func_ov001_0206c924();
    }
}
