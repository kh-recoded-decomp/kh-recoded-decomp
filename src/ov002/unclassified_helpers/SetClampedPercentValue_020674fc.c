#include "nitro/types.h"

extern void func_02027360(s32 recordId, s32 index, s32 value);

void SetClampedPercentValue_020674fc(s32 value) {
    if (value < 0) {
        value = 0;
    } else if (100 < value) {
        value = 100;
    }
    func_02027360(0x9f0, 7, value);
}
