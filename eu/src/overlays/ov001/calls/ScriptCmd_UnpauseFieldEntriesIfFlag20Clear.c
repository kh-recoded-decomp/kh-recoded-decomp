#include "nitro/types.h"

extern u32 GetSessionFlagsMask20();
extern u32 SetFieldEntriesPaused();

u32 ScriptCmd_UnpauseFieldEntriesIfFlag20Clear(void) {
    s32 result = GetSessionFlagsMask20();
    if (result == 0) {
        SetFieldEntriesPaused(0);
        return 1;
    }
    return 0;
}
