#include "nitro/types.h"

extern u32 data_0205fe0c;
extern u32 ApplyCategoryRecord(u32 target, u32 param1, u32 param2);

void func_ov002_0206793c(u32 param1, u32 param2, u32 *outValue) {
    u32 result = ApplyCategoryRecord(data_0205fe0c + 0x276c, param1, param2);
    if (outValue != NULL) {
        *outValue = result;
    }
}
