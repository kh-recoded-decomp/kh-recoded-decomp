#include "nitro/types.h"

extern BOOL IsSessionFlagSet(u32 flag);
extern int GetScriptHandlerSlot7Index(void);
extern int GetManagedActorCount(void);
extern BOOL IsSlot7HandlerIndex7Flag370dSet(void);

BOOL IsPartyGaugeGainAllowed(void)
{
    BOOL result = TRUE;

    if (IsSessionFlagSet(0x3609) != 0 || IsSessionFlagSet(0x360a) != 0) {
        if (GetManagedActorCount() <= 2) {
            result = FALSE;
        }
    } else if (IsSessionFlagSet(0x360b) != 0) {
        result = FALSE;
    } else {
        if (GetScriptHandlerSlot7Index() == 7 && IsSessionFlagSet(0x370c) != 0) {
            result = FALSE;
        }
        if (IsSlot7HandlerIndex7Flag370dSet() != 0) {
            result = FALSE;
        }
    }
    return result;
}
