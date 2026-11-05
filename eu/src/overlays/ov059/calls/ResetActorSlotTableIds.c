#include "nitro/types.h"

extern void SlotTable_ResetIds(u32 context);

void ResetActorSlotTableIds(u32 context)
{
    SlotTable_ResetIds(context + 3780);
}
