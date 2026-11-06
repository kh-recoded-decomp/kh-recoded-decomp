#include "nitro/types.h"

extern u32 gCounterHudWork;
extern u32 sOv001_Adnum_0209f004;
extern u32 sOv001_W_0209f00c;
extern void MI_CpuFill8(void *dest, s32 value, u32 size);
extern void *GetRunningTaskWork(void);
extern void LoadCounterHudResource();
extern int UpdateAndDrawCounterHud(void);

u32 InitCounterHudWork(void)
{
    u8 *context;

    context = GetRunningTaskWork();
    MI_CpuFill8(context, 0, 0x910);
    gCounterHudWork = (u32)context;
    LoadCounterHudResource(context + 8, &sOv001_Adnum_0209f004);
    LoadCounterHudResource(context + 0xc, &sOv001_W_0209f00c);
    *(u32 *)(context + 0xe8) = 0x23000;
    *(u32 *)(context + 0xec) = 0x7000;
    return (u32)UpdateAndDrawCounterHud;
}
