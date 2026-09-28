#include "nitro/types.h"

extern u32 data_ov001_0209e9fc;
extern void *PXI_Init_0202a638();
extern BOOL func_ov001_02066e38(void);

void func_ov001_02066e18(void)
{
    BOOL active;

    active = func_ov001_02066e38();
    if (active != 0) {
        PXI_Init_0202a638(data_ov001_0209e9fc);
        data_ov001_0209e9fc = 0xffffffff;
    }
}
