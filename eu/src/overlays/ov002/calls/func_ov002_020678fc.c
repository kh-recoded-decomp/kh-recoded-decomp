#include "nitro/types.h"

extern u32 data_0205fe0c;
extern u32 ApplyRecordsToPackedFields(u32 target, s32 *entryIds, s32 entryCount);

void func_ov002_020678fc(s32 entryId, u32 *outResult) {
    u32 result = ApplyRecordsToPackedFields(data_0205fe0c + 0x276c, &entryId, 1);
    if (outResult != NULL) {
        *outResult = result;
    }
}
