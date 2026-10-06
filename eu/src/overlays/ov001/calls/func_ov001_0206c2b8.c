#include "nitro/types.h"

extern u32 func_ov001_0206c2c8(void);
extern u32 func_ov001_0206c2e0(void);

u32 func_ov001_0206c2b8(void)
{
    u32 a;
    u32 b;

    a = func_ov001_0206c2c8();
    b = func_ov001_0206c2e0();
    return b | a;
}
