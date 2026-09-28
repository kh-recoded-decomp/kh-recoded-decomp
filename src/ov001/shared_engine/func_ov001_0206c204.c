#include "nitro/types.h"

extern int FreeBufferAndClearStatus_0206a918(int obj);

void func_ov001_0206c204(int manager)
{
    FreeBufferAndClearStatus_0206a918(manager);
    FreeBufferAndClearStatus_0206a918(manager + 0x30);
}
