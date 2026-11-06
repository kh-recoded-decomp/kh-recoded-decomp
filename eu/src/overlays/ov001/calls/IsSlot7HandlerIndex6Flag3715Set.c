#include "nitro/types.h"

extern int IsSessionFlagSet(u32 flag);
extern int GetScriptHandlerSlot7Index(void);

BOOL IsSlot7HandlerIndex6Flag3715Set(void)
{
    int value;

    value = GetScriptHandlerSlot7Index();
    if ((value == 6) && (value = IsSessionFlagSet(0x3715), value != 0)) {
        return 1;
    }
    return 0;
}
