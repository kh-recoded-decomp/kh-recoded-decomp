#include "nitro/types.h"

extern u32 g_panel_020d0ea0;

extern void func_ov044_020d0200(void);

void SetPanelState_020d0278(u32 state, u32 data)
{
    *(u32 *)(g_panel_020d0ea0 + 0x40) = *(u32 *)(g_panel_020d0ea0 + 0x44);
    *(u32 *)(g_panel_020d0ea0 + 0x44) = state;
    *(u32 *)(g_panel_020d0ea0 + 0x64) = 0;
    *(u32 *)(g_panel_020d0ea0 + 0x68) = data;
    *(u32 *)(g_panel_020d0ea0 + 0x6c) = 1;
    func_ov044_020d0200();
}
