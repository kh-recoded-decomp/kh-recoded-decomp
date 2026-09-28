#include "nitro/types.h"

extern u32 g_fieldContext_020bb380;
extern void PXI_Init_0202a638();
extern void func_0204df9c();
extern void func_ov001_02063c54(void);
extern void func_ov001_020667b4(void);
extern void func_ov001_0206a714(void);
extern void ArmObject_0206c6f4(void);

void ReleaseFieldContext_020ba60c(void)
{
    func_0204df9c(0);
    PXI_Init_0202a638(*(u32 *)(g_fieldContext_020bb380 + 0x18));
    PXI_Init_0202a638(*(u32 *)(g_fieldContext_020bb380 + 0x1c));
    func_ov001_020667b4();
    if (*(s32 *)(g_fieldContext_020bb380 + 0x14) != -1) {
        func_ov001_0206a714();
        *(u32 *)(g_fieldContext_020bb380 + 0x14) = 0xffffffff;
    }
    ArmObject_0206c6f4();
    func_ov001_02063c54();
    g_fieldContext_020bb380 = 0;
}
