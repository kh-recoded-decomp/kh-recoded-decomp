#include "nitro/types.h"

extern u32 gSaveIoStateDataTail;
extern u32 MarkRecordFlagBits(u32 target, u32 param);

void MarkGlobalMenuRecordFlagBits(u32 param, u32 *outValue) {
    u32 result = MarkRecordFlagBits(gSaveIoStateDataTail + 0x2788, param);
    if (outValue != NULL) {
        *outValue = result;
    }
}
