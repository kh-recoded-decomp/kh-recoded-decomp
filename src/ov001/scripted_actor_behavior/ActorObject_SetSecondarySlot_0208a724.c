#include "nitro/types.h"

extern void func_01ff89a8(const void *src, void *dest, u32 len);

void ActorObject_SetSecondarySlot_0208a724(u8 *actor, const void *src, int index)
{
    func_01ff89a8(src, actor + 0x820 + index * 8, 8);
}
