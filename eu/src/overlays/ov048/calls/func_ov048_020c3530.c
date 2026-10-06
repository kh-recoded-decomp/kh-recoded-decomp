#include "nitro/types.h"

extern void UpdateOrbitCameraInput(void);
extern void func_ov048_020c37ac(u32 context, u32 data);
extern void StartCameraDrift(u32 context, u32 data);

u32 func_ov048_020c3530(u32 context, u32 data)
{
    UpdateOrbitCameraInput();
    func_ov048_020c37ac(context, data);
    StartCameraDrift(context, data);
    return 0;
}
