#include "nitro/types.h"

extern void func_01ff89a8(const void *src, void *dest, u32 len);

void ActorObject_SetExtraSlot_0208aa98(u8 *actor, const void *src, int index)
{
    func_01ff89a8(src, actor + 0x870 + index * 0xc, 0xc);
}
