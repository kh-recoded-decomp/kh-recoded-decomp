#include "nitro/types.h"

extern u32 g_panel_020d0ea0;

extern void func_01ff9e3c();
extern u32 FX_Div_020d0080();
extern void func_0204dc94();

void func_ov044_020d0090(BOOL shouldBlend)
{
    u32 panel;
    u8 blended[12];

    panel = g_panel_020d0ea0;
    if ((*(u32 *)(g_panel_020d0ea0 + 0x38) & 2) == 0) {
        if (shouldBlend) {
            func_01ff9e3c(g_panel_020d0ea0 + 0x14, g_panel_020d0ea0 + 0x20, blended);
            func_0204dc94(panel + 0x20, blended, panel + 0x2c);
        }
        FX_Div_020d0080(panel);
    }
}
