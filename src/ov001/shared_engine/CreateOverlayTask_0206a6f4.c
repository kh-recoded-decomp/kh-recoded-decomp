#include "nitro/types.h"

extern void *func_0202a448(void *descriptor, void *userData);

extern u8 data_ov001_0209eaec[];
extern void *g_overlayTask_0209eae8;

void CreateOverlayTask_0206a6f4(u32 firstArg, ...)
{
    g_overlayTask_0209eae8 = func_0202a448(data_ov001_0209eaec, &firstArg);
}
