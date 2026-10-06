#include "nitro/types.h"

extern u32 data_ov001_020a0498;
extern s32 ReleaseTaskNode(void);
extern void MIi_CpuClear16(u32 value, void *dest, u32 size);

void func_ov001_020691d4(void)
{
    s32 node;

    node = *(s32 *)(*(u32 *)(data_ov001_020a0498 + 0x34) + 4);
    while (node != 0) {
        if (*(u16 *)(node + 0x50) < 0xf8) {
            node = *(s32 *)(node + 4);
        } else {
            node = ReleaseTaskNode();
        }
    }
    MIi_CpuClear16(0xffff, (void *)data_ov001_020a0498, 0x10);
    *(u8 *)(data_ov001_020a0498 + 0x10) = 0;
}
