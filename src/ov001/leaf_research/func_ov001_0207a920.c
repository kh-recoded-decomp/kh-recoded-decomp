#include "nitro/types.h"

extern void FSi_WaitForCardThread_01ff8140(void);
extern void func_0200b850(void *info, u32 flag, u32 count);
extern void func_0200b9b0(void *info, void *queue);

void func_ov001_0207a920(s32 panel, u32 count)
{
    FSi_WaitForCardThread_01ff8140();
    func_0200b850((void *)(panel + 0xa4), 0, count);
    func_0200b9b0((void *)(panel + 0xa4), (void *)(panel + 0x5c));
}
