#include "nitro/types.h"

extern int FreeBufferAndClearStatus(int obj);

void func_ov001_0206c204(int manager)
{
    FreeBufferAndClearStatus(manager);
    FreeBufferAndClearStatus(manager + 0x30);
}
