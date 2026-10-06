#include "nitro/types.h"

extern void FSi_WaitForCardThread(void);
extern void FS_LoadOverlayInfo(void *info, u32 flag, u32 count);
extern void FS_LoadOverlayImageAsync(void *info, void *queue);

void func_ov001_0207a920(s32 panel, u32 count)
{
    FSi_WaitForCardThread();
    FS_LoadOverlayInfo((void *)(panel + 0xa4), 0, count);
    FS_LoadOverlayImageAsync((void *)(panel + 0xa4), (void *)(panel + 0x5c));
}
