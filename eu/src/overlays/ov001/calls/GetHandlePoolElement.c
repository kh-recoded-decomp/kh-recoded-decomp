#include "src/overlays/ov001/HandlePool.h"

void *GetHandlePoolElement(HandlePool *pool, int handle)
{
    return pool->elements + pool->elementSize * (u16)(handle - 1);
}
