#include "nitro/types.h"

extern u32 data_ov001_0209ea1c;
extern void *PXI_Init_0202a64c();
extern BOOL func_ov001_02066e38(void);

void func_ov001_02066e18(void)
{
    BOOL active;

    active = func_ov001_02066e38();
    if (active != 0) {
        PXI_Init_0202a64c(data_ov001_0209ea1c);
        data_ov001_0209ea1c = 0xffffffff;
    }
}
