#include "nitro/types.h"

extern void func_ov001_020888dc(void);

u32 ScriptOp_RunActorPass_0208de98(u8 *scriptContext)
{
    if (*(u32 *)(*(u8 **)(scriptContext + 0x1c8) + 0x4c) != 0) {
        func_ov001_020888dc();
    }
    return 1;
}
