#include "nitro/types.h"

extern void PXI_Init_0202a638(void);
extern void FS_RunOverlayCleanupCallbacks_0200bc64(void *info);
extern void FS_UnloadOverlayImage_0200bd54(void *info);

void func_ov001_0207a944(s32 *panel)
{
    if (*panel != 0) {
        PXI_Init_0202a638();
        *panel = 0;
        FS_RunOverlayCleanupCallbacks_0200bc64(panel + 0x29);
        FS_UnloadOverlayImage_0200bd54(panel + 0x29);
    }
}
