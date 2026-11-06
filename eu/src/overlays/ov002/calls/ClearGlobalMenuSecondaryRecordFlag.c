#include "nitro/types.h"

extern u32 gSaveIoStateDataTail;
extern void SetRecordFlagFromTable(u32 target, u32 param1, u32 param2, u32 zero1, u32 zero2);

void ClearGlobalMenuSecondaryRecordFlag(u32 param1, u32 param2) {
    SetRecordFlagFromTable(gSaveIoStateDataTail + 0x2788, param1, param2, 0, 0);
}
