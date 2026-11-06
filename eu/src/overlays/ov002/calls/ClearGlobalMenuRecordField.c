#include "nitro/types.h"

extern u32 gSaveIoStateDataTail;
extern u32 ClearPackedField(u32 target, u32 param1, u32 param2);

void ClearGlobalMenuRecordField(u32 param1, u32 param2, u32 *outValue) {
    u32 result = ClearPackedField(gSaveIoStateDataTail + 0x276c, param1, param2);
    if (outValue != NULL) {
        *outValue = result;
    }
}
