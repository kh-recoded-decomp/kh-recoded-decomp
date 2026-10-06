#include "nitro/types.h"

extern u32 func_ov001_0207b3f4(void);
extern void ResetMenuLayerTransforms(void);

void func_ov001_0207b5f4(void)
{
    u32 fault;

    fault = func_ov001_0207b3f4();
    if (fault == 2) {
        ResetMenuLayerTransforms();
    }
}
