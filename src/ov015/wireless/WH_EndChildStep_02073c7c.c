#include "nitro/types.h"

extern char data_ov015_0207f3a0[];
extern int PXI_Init_02012284(void *arg);
extern void WH_SetError_020737d4(int code);
extern int func_ov015_02073cbc(void);
extern void PollPanelTransition_02074e80(void);

BOOL WH_EndChildStep_02073c7c(void)
{
    int error = PXI_Init_02012284(data_ov015_0207f3a0);

    if (error != 0) {
        WH_SetError_020737d4(error);
        return FALSE;
    }
    if (func_ov015_02073cbc() != 0) {
        return TRUE;
    }
    PollPanelTransition_02074e80();
    return FALSE;
}
