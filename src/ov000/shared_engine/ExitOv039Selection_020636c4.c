#include "nitro/types.h"

extern void *data_ov000_02063a08;
extern char OverlayId39_00000027[];

extern void func_02029f98(int processor, int overlayId);

void ExitOv039Selection_020636c4(void)
{
    func_02029f98(0, (int)OverlayId39_00000027);
    data_ov000_02063a08 = NULL;
}
