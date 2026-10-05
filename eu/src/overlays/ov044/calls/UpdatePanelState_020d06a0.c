<<<<<<< HEAD
#define UpdatePanelState_020d0680 UpdatePanelState_020d06a0
#define func_ov044_020d032c func_ov044_020d034c
#define func_ov044_020d0944 UpdatePanelCamera
#define g_panel_020d0ea0 data_ov044_020d0ec0
#include "src/ov044/panel_state/UpdatePanelState_020d0680.c"
=======
#include "nitro/types.h"

extern u32 data_ov044_020d0ec0;

extern void StepPanelTransition(void);
extern void UpdatePanelCamera(void);

u32 UpdatePanelState_020d06a0(void)
{
    s32 prevState = *(s32 *)(data_ov044_020d0ec0 + 0x40);
    s32 state = *(s32 *)(data_ov044_020d0ec0 + 0x44);

    if (prevState != state || prevState == 6) {
        StepPanelTransition();
    }
    UpdatePanelCamera();
    return 0;
}
>>>>>>> 6429ce2ea7ff13b674e183a6843387d9844d00d4
