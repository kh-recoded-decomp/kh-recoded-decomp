#include "nitro/types.h"

extern BOOL IsSessionFlagSet(u32 flag);
extern int GetScriptHandlerSlot7Index(void);
extern int GetManagedActorCount(void);
extern BOOL func_ov001_0206e2b0(void);

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
        if (func_ov001_0206e2b0() != 0) {
            result = FALSE;
        }
    }
    return result;
}
