#include "nitro/types.h"

extern u32 SetPendingFieldValue();

u32 func_ov001_02065e8c(s32 entry) {
    SetPendingFieldValue(3);
    *(u32 *)(entry + 0x1cc) = 0;
    return 3;
}
