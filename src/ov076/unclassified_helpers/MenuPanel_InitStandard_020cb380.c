#include "nitro/types.h"

extern void func_ov076_020cb3a8(void *panel, int owner, int x, int y, u16 width, u16 height, int priority, int arg7, int arg8);

void MenuPanel_InitStandard_020cb380(void *panel, int owner, int x, int y, u16 width, u16 height, int arg7)
{
    func_ov076_020cb3a8(panel, owner, x, y, width, height, 0x96, arg7, 0x412);
}
