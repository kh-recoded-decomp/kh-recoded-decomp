#include "nitro/types.h"

extern u8 g_defaultPanelData_0209ef68;
extern u32 g_activePanel_020a04c8;

u8 *func_ov001_0207b180(void)
{
    u8 *data;

    if ((g_activePanel_020a04c8 == 0) ||
        (data = *(u8 **)(g_activePanel_020a04c8 + 0x18), data == (u8 *)0x0)) {
        data = &g_defaultPanelData_0209ef68;
    }
    return data;
}
