#include "nitro/types.h"

typedef struct {
    u8 pad_00[0x66cc];
    void *overlayTask;
} Panel;

extern char OverlayId3_00000003[];

extern void PXI_Init_0202a638(void *task);
extern void func_02029f98(int processor, int overlayId);
extern void SetupDisplayBanksAndLayers_0206141c(Panel *panel);

void ReleaseTitleOverlayTask_02062f0c(Panel *panel)
{
    PXI_Init_0202a638(panel->overlayTask);
    panel->overlayTask = NULL;
    func_02029f98(0, (int)OverlayId3_00000003);
    SetupDisplayBanksAndLayers_0206141c(panel);
}
