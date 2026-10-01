#include "nitro/types.h"

extern void func_02015274(void *entry, int fourth, int third, u16 fifth);

void SetupSlotEntry_0204f4a4(u8 *owner, int index, int third, int fourth, u16 fifth)
{
    func_02015274(owner + 0x18 + index * 0x8c, fourth, third, fifth);
}
