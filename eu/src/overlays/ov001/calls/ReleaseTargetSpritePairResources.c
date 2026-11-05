#include "nitro/types.h"

extern int FreeBufferAndClearStatus(int obj);

void ReleaseTargetSpritePairResources(int manager)
{
    FreeBufferAndClearStatus(manager);
    FreeBufferAndClearStatus(manager + 0x30);
}
