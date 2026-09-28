#include "nitro/types.h"

extern u8 *g_stageManager_020a0508;
extern void PXI_Init_0202a638(u32 handle);

BOOL ReleaseStageManager_0209b8c4(void)
{
    if (g_stageManager_020a0508 != 0) {
        PXI_Init_0202a638(*(u32 *)(g_stageManager_020a0508 + 4));
        g_stageManager_020a0508 = 0;
    }
    return TRUE;
}
