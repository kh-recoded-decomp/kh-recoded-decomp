#include "nitro/types.h"

extern u32 gSaveIoStateDataTail;
extern u32 ApplyCategoryRecord(u32 target, u32 param1, u32 param2);

void ApplyGlobalMenuCategoryRecord(u32 param1, u32 param2, u32 *outValue) {
    u32 result = ApplyCategoryRecord(gSaveIoStateDataTail + 0x276c, param1, param2);
    if (outValue != NULL) {
        *outValue = result;
    }
}
