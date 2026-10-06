#include "nitro/types.h"

extern s32 func_ov001_0207b3f4(void);
extern s32 func_ov001_0207b61c(void);
extern void ActivatePanelEntity(void);

u32 func_ov001_0207b77c(void)
{
    if (func_ov001_0207b3f4() != 2) {
        return 0;
    }
    if (func_ov001_0207b61c() == 0) {
        return 0;
    }
    ActivatePanelEntity();
    return 1;
}
