#include "nitro/types.h"

extern BOOL func_ov001_020645c8(u32 flag);
extern void func_ov001_020877dc(void);
extern void func_ov001_020877f4(void);

u32 ScriptOp_InitSubsystemIfFlagClear_0208edf0(void)
{
    BOOL flagSet;

    flagSet = func_ov001_020645c8(0x3528);
    if (flagSet == 0) {
        func_ov001_020877dc();
        func_ov001_020877f4();
    }
    return 1;
}
