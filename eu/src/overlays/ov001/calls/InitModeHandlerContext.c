/* Preserve the original wrapper's CodeWarrior integer types. */
#include "../include/nitro/types.h"

#include "nitro/types.h"

/* The task runner consumes native 32-bit callback words; zero retains its current state. */
extern u32 RunActiveModeHandler(void);

extern u32 GetRunningTaskWork(void);
extern void MI_CpuFill8(void *dst, u8 val, u32 size);
extern u32 MakePrimaryVramKey_02071248(u32 size);
extern u32 Archive_LoadFile(u32 block, u32 align);
extern void InitTween(void *obj);

extern u32 gMessageWindowWork;

u32 InitModeHandlerContext(void)
{
    u32 context;
    u32 block;

    context = GetRunningTaskWork();
    gMessageWindowWork = context;
    MI_CpuFill8((void *)context, 0, 0xfc);
    *(u32 *)(context + 4) = 0;
    block = MakePrimaryVramKey_02071248(0x2d);
    block = Archive_LoadFile(block, 0xe);
    *(u32 *)(context + 0xd0) = block;
    *(u32 *)(context + 0xf8) = 1;
    InitTween((void *)(context + 0xd8));
    return (u32)RunActiveModeHandler;
}
