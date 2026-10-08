#include "nitro/types.h"

extern u32 func_ov001_02063838();
extern u32 SetFieldEntriesPaused();

u32 func_ov001_02065200(void) {
    s32 result = func_ov001_02063838();
    if (result == 0) {
        SetFieldEntriesPaused(0);
        return 1;
    }
    return 0;
}
