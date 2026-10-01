#include "nitro/types.h"

typedef struct {
    u8 pad_00[0x6690];
    u32 pxiHandle;
} Panel;

extern u32 func_ov000_02063770(void);
extern void PXI_Init_0202a638(u32 handle);
extern void SetupDisplayBanksAndLayers_0206141c(Panel *panel);

void ReleaseHandleAndResetDisplay_02062cf4(Panel *panel)
{
    BOOL needsReset = FALSE;

    if (func_ov000_02063770() == 2) {
        needsReset = TRUE;
    }
    PXI_Init_0202a638(panel->pxiHandle);
    panel->pxiHandle = 0;
    if (needsReset) {
        SetupDisplayBanksAndLayers_0206141c(panel);
    }
}
