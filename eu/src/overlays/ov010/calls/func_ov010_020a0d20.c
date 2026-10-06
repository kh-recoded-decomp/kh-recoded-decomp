#include "nitro/types.h"

extern void RestartObjectEffect(void);
extern void ClearSessionPackedBit(int eventId);

void func_ov010_020a0d20(u32 *actor)
{
    *actor = 0;
    RestartObjectEffect();
    ClearSessionPackedBit(0x3713);
    ClearSessionPackedBit(0x3716);
    ClearSessionPackedBit(0x3717);
}
