#include "nitro/types.h"

extern u32 gSaveIoStateDataTail;
extern u32 ApplyRecordsToPackedFields(u32 target, s32 *entryIds, s32 entryCount);

void ApplySingleGlobalMenuRecord(s32 entryId, u32 *outResult) {
    u32 result = ApplyRecordsToPackedFields(gSaveIoStateDataTail + 0x276c, &entryId, 1);
    if (outResult != NULL) {
        *outResult = result;
    }
}
