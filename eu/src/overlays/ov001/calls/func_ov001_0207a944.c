#include "nitro/types.h"

extern void PXI_Init_0202a64c(void);
extern void FS_EndOverlay(void *info);
extern void FS_UnloadOverlayImage(void *info);

void func_ov001_0207a944(s32 *panel)
{
    if (*panel != 0) {
        PXI_Init_0202a64c();
        *panel = 0;
        FS_EndOverlay(panel + 0x29);
        FS_UnloadOverlayImage(panel + 0x29);
    }
}
