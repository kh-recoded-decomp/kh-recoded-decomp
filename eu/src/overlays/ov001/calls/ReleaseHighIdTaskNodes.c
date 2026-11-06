#include "nitro/types.h"

extern u32 gFieldTaskManagerWork;
extern s32 ReleaseTaskNode(void);
extern void MIi_CpuClear16(u32 value, void *dest, u32 size);

void ReleaseHighIdTaskNodes(void)
{
    s32 node;

    node = *(s32 *)(*(u32 *)(gFieldTaskManagerWork + 0x34) + 4);
    while (node != 0) {
        if (*(u16 *)(node + 0x50) < 0xf8) {
            node = *(s32 *)(node + 4);
        } else {
            node = ReleaseTaskNode();
        }
    }
    MIi_CpuClear16(0xffff, (void *)gFieldTaskManagerWork, 0x10);
    *(u8 *)(gFieldTaskManagerWork + 0x10) = 0;
}
