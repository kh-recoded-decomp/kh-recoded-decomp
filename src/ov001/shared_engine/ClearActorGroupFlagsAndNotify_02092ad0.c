#include "nitro/types.h"

extern void *func_ov001_0209c040(s16 groupId);
extern void *func_ov001_0209c2f0(void *node);
extern void func_ov001_02091964(void *node);

void ClearActorGroupFlagsAndNotify_02092ad0(u8 *actor)
{
    void *node;

    *(u8 *)(actor + 0x1b4) = 0;
    *(u8 *)(actor + 0x1b5) = 0;
    for (node = func_ov001_0209c040(*(s16 *)(actor + 0x10)); node != 0; node = func_ov001_0209c2f0(node)) {
        func_ov001_02091964(node);
    }
}
