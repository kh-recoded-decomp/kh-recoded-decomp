#include "nitro/types.h"

extern s32 func_ov001_0207b3f4(void);
extern s32 func_ov001_0207b610(void);
extern void LookupChannelEntry_020b62ac(u32 value);
extern void DrawNumberInPanelSlot(void);

void func_ov001_0207b668(u32 value)
{
    if (func_ov001_0207b3f4() == 2 && func_ov001_0207b610() != 0) {
        DrawNumberInPanelSlot();
        LookupChannelEntry_020b62ac(value);
    }
}
