#include "nitro/types.h"

extern u32 ActorSlot_IsFlag8SetByIndex();

void
GetFieldObjectActorSlotFlag8(int self)
{
    ActorSlot_IsFlag8SetByIndex(*(u8 *)(self + 0x38));
}
