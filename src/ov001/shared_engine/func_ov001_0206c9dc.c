#include "nitro/types.h"

extern void func_ov001_0206c994(int obj);
extern void func_0202a1c4(u32 obj);

extern u32 g_obj_020a0498;

void func_ov001_0206c9dc(void)
{
    if (g_obj_020a0498 != 0) {
        func_ov001_0206c994(g_obj_020a0498);
        func_0202a1c4(g_obj_020a0498);
        g_obj_020a0498 = 0;
    }
}
