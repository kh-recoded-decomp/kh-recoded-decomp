#include "nitro/types.h"

extern u8 gScriptState;

u32 SetScriptBgmSelection(u32 selection)
{
    gScriptState = (u8)selection;
    return selection;
}
