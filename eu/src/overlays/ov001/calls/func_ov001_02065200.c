#include "nitro/types.h"

extern u32 GetSessionFlagsMask20();
extern u32 SetFieldEntriesPaused();

u32 func_ov001_02065200(void) {
    s32 result = GetSessionFlagsMask20();
    if (result == 0) {
        SetFieldEntriesPaused(0);
        return 1;
    }
    return 0;
}
