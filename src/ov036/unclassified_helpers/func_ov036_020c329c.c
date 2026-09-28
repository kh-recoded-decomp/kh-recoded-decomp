#include "nitro/types.h"

extern void func_020011a4(u32 value);
extern void func_ov036_020c30e4(void);
extern void func_020285a0(u32 value);

u32 func_ov036_020c329c(u32 value)
{
    func_020011a4(1);
    func_ov036_020c30e4();
    func_020285a0(value);
    return 1;
}
