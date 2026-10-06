#include "nitro/types.h"

extern void func_ov001_0207a920(s32 panel, u32 count);
extern void func_ov001_0207a944(s32 panel);
extern u32 StepSubScreenFade(void);
extern u32 IsFileLoadQueueEmpty(void);

void func_ov001_0207abdc(s32 panel)
{
    u32 ready;

    ready = StepSubScreenFade();
    if ((ready != 0) && (ready = IsFileLoadQueueEmpty(), ready != 0)) {
        *(u32 *)(panel + 0xdc) = 0xffffffff;
        func_ov001_0207a944(panel);
        func_ov001_0207a920(panel, *(u32 *)(panel + 0xd0));
        *(u32 *)(panel + 0x4c) = 0;
        *(u32 *)(panel + 0x30) = 2;
    }
}
