#include "nitro/types.h"

extern void *func_ov001_0209c2dc(u16 groupId);
extern void *func_ov001_0209c2f0(void *node);
extern void func_ov001_0209178c(void *node, u32 message);

void NotifyActorGroupMembers_020969e0(u8 *actor, u32 message)
{
    void *node;

    for (node = func_ov001_0209c2dc(*(u16 *)(actor + 0x10)); node != 0; node = func_ov001_0209c2f0(node)) {
        func_ov001_0209178c(node, message);
    }
}
