#include "nitro/types.h"

extern void AdvancePool0Timer_020a4278(void);
extern void StepLinearPathMotion_020a42f8(void);
extern void StepOrbitMotion_020a4420(void);
extern void UpdateOwnerFall_020a48cc(void);
extern void func_ov017_020a466c(void);

void (*const data_ov017_020a5e28[5])(void) = {
    AdvancePool0Timer_020a4278,
    StepLinearPathMotion_020a42f8,
    StepOrbitMotion_020a4420,
    func_ov017_020a466c,
    UpdateOwnerFall_020a48cc,
};
