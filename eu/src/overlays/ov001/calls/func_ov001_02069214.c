#include "nitro/types.h"

extern u32 data_ov001_020a0498;
extern void ReleaseLowIdTaskNodes(void);
extern void func_ov001_020691d4(void);

void func_ov001_02069214(void)
{
    u32 ctx;

    ctx = data_ov001_020a0498;
    ReleaseLowIdTaskNodes();
    func_ov001_020691d4();
    *(u8 *)(ctx + 0x11) = 0;
}
