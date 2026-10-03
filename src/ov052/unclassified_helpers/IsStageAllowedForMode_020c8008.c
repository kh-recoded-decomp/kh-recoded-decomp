#include "nitro/types.h"

extern int func_ov001_02067ed4(void);
extern signed char GetCtxModeByte_02068084(void);

BOOL IsStageAllowedForMode_020c8008(void)
{
    BOOL result = FALSE;
    int stage = func_ov001_02067ed4();
    switch (GetCtxModeByte_02068084()) {
    case 1:
        if (stage == 1) {
            result = TRUE;
        }
        break;
    case 6:
        if (stage == 10) {
            result = TRUE;
        }
        break;
    case 7:
        if (stage == 5 || stage == 7) {
            result = TRUE;
        }
        break;
    }
    return result;
}
