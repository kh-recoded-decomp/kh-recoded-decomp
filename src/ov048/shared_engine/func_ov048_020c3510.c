#include "nitro/types.h"

extern void func_ov048_020c3530(void);
extern void func_ov048_020c378c(u32 context, u32 data);
extern void func_ov048_020c379c(u32 context, u32 data);

u32 func_ov048_020c3510(u32 context, u32 data)
{
    func_ov048_020c3530();
    func_ov048_020c378c(context, data);
    func_ov048_020c379c(context, data);
    return 0;
}
