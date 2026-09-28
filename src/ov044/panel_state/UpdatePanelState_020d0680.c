#include "nitro/types.h"

extern u32 g_panel_020d0ea0;

extern void func_ov044_020d032c(void);
extern void func_ov044_020d0944(void);

u32 UpdatePanelState_020d0680(void)
{
    s32 prevState = *(s32 *)(g_panel_020d0ea0 + 0x40);
    s32 state = *(s32 *)(g_panel_020d0ea0 + 0x44);

    if (prevState != state || prevState == 6) {
        func_ov044_020d032c();
    }
    func_ov044_020d0944();
    return 0;
}
