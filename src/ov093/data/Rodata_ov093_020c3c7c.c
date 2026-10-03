#include "nitro/types.h"

extern void WaitForBrightnessReset_020c2358(void);
extern void func_ov093_020c2354(void);
extern void func_ov093_020c23a8(void);
extern void func_ov093_020c2610(void);
extern void func_ov093_020c2850(void);
extern void func_ov093_020c2950(void);
extern void func_ov093_020c2b00(void);

void (*const data_ov093_020c3c7c[7])(void) = {
    func_ov093_020c2354,
    WaitForBrightnessReset_020c2358,
    func_ov093_020c23a8,
    func_ov093_020c2610,
    func_ov093_020c2850,
    func_ov093_020c2950,
    func_ov093_020c2b00,
};
