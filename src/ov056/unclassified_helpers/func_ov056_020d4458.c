#include "nitro/types.h"

extern void func_ov021_020aeb84(void);
extern void func_ov056_020d7e74(int target, u32 value);

void func_ov056_020d4458(int actor, u32 value)
{
    func_ov021_020aeb84();
    func_ov056_020d7e74(actor + 0x18c, value);
}
