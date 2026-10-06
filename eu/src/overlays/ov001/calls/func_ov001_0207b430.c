#include "nitro/types.h"

extern u32 func_ov001_0207a8fc();
extern void ResetMapMenuScreen(void);

extern u32 data_ov001_020a04e8;

void func_ov001_0207b430(void)
{
    u32 ready;

    *(u32 *)(data_ov001_020a04e8 + 0x50) = 0xfffffffe;
    ready = func_ov001_0207a8fc();
    if (ready != 0) {
        ResetMapMenuScreen();
    }
}
