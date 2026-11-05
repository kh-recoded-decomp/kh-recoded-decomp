#include "nitro/types.h"

extern u32 GetFieldEntryByPoolAndIndex();
extern void DispatchActorCollision();

void DispatchIndexedFieldObjectCollision(u32 unused1, u32 unused2, u32 param3, u32 param4)
{
    u32 context;

    context = GetFieldEntryByPoolAndIndex();
    DispatchActorCollision(context, param3, param4);
}
