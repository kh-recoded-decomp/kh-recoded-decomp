#include "nitro/types.h"

extern int IsSessionFlagSet(u32 flag);
extern int GetScriptHandlerSlot7Index(void);

BOOL func_ov001_0206e2b0(void)
{
    int value;

    value = GetScriptHandlerSlot7Index();
    if ((value == 7) && (value = IsSessionFlagSet(0x370d), value != 0)) {
        return 1;
    }
    return 0;
}
