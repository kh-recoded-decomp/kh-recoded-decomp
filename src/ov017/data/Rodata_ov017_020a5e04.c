#include "nitro/types.h"

extern void ComputePool1Progress_020a42b0(void);
extern void ComputePool2Target_020a43ec(void);
extern void CopyPool3Entry_020a44d0(void);
extern void ResetFallTarget_020a48bc(void);
extern void Word_Clear_020a4270(void);
extern void func_ov017_020a4be0(void);

void (*const data_ov017_020a5e14[5])(void) = {
    Word_Clear_020a4270,
    ComputePool1Progress_020a42b0,
    ComputePool2Target_020a43ec,
    CopyPool3Entry_020a44d0,
    ResetFallTarget_020a48bc,
};

void (*const data_ov017_020a5e04[4])(void) = {
    func_ov017_020a4be0,
    NULL,
    NULL,
    NULL,
};
