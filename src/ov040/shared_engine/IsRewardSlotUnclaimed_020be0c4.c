#include "nitro/types.h"

extern u32 func_ov040_020bdc24(u32 code);
extern int GetPlayerFlagRecord_0205036c(int index);

BOOL IsRewardSlotUnclaimed_020be0c4(void *unused, u32 code)
{
    int i;
    BOOL result = TRUE;
    int flagId = func_ov040_020bdc24(code);

    for (i = 0; i < 8; i++) {
        s16 value = *(s16 *)GetPlayerFlagRecord_0205036c(i);
        if (value == flagId || value == -1) {
            result = FALSE;
            break;
        }
    }
    return result;
}

