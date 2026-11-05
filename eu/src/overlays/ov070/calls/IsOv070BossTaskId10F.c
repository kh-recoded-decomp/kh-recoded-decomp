#include "nitro/types.h"

BOOL IsOv070BossTaskId10F(s32 *value) {
    if (*value == 0x10f) {
        return 1;
    }
    return 0;
}
