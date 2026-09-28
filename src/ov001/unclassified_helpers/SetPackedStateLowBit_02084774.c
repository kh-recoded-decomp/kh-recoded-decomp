#include "nitro/types.h"

extern u16 func_ov001_0207f9a8(void *object);
extern void func_ov001_0207f9c8(void *object, u16 state);

void SetPackedStateLowBit_02084774(void *object, u16 lowBit)
{
    u16 state = func_ov001_0207f9a8(object);
    func_ov001_0207f9c8(object, lowBit | (state & ~1));
}
