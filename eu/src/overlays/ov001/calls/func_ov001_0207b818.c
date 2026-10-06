#include "nitro/types.h"

extern u32 data_ov001_020a04ec;
extern u32 sOv001_Adnum_0209f004;
extern u32 sOv001_W_0209f00c;
extern void MI_CpuFill8(void *dest, s32 value, u32 size);
extern void *NNSi_FndGetCurrentRootHeap(void);
extern void func_ov001_0207b7e4();
extern void func_ov001_0207b888(void);

u32 func_ov001_0207b818(void)
{
    u8 *context;

    context = NNSi_FndGetCurrentRootHeap();
    MI_CpuFill8(context, 0, 0x910);
    data_ov001_020a04ec = (u32)context;
    func_ov001_0207b7e4(context + 8, &sOv001_Adnum_0209f004);
    func_ov001_0207b7e4(context + 0xc, &sOv001_W_0209f00c);
    *(u32 *)(context + 0xe8) = 0x23000;
    *(u32 *)(context + 0xec) = 0x7000;
    return (u32)func_ov001_0207b888;
}
