#include "nitro/types.h"

extern u32 LookupTableOffset(s32 category, u32 param3);
extern u32 GetRecordFlagState(u32 param1, u32 value, u32 param4);

u32 func_ov002_02069b8c(u32 param1, s32 category, u32 param3, u32 param4) {
    u32 value = LookupTableOffset(category, param3);
    if (category != 0x12) {
        return GetRecordFlagState(param1, value, param4);
    }
    return 0;
}
