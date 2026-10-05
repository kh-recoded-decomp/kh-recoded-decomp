#include "nitro/types.h"

extern void *data_02063a04;
extern char OverlayId27_0000001b[];
extern char OverlayId39_00000027[];

extern void ShutdownOverlay_020bbe60(int arg);
extern void func_02029f98(int processor, int overlayId);

void ExitWorldSession_020635d4(void)
{
    ShutdownOverlay_020bbe60(0);
    func_02029f98(0, (int)OverlayId39_00000027);
    func_02029f98(0, (int)OverlayId27_0000001b);
    data_02063a04 = NULL;
}
