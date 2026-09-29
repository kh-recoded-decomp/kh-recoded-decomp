#include "nitro/types.h"

extern void GetModeDataRegion_0208698c(u32 *offset, u32 *size);
extern BOOL IsGameFlagSet_020645c8(u32 flagIndex);
extern u16 IsEntryFlagSet_0208696c(u32 entryId, u32 slot);

int GetEntryUnlockState_02087478(BOOL skipModeCheck, u32 flagOffset, u32 entryId, u32 slot)
{
    u32 regionOffset;
    u32 size;

    if (!skipModeCheck) {
        GetModeDataRegion_0208698c(&regionOffset, &size);
        if (!IsGameFlagSet_020645c8(regionOffset + flagOffset)) {
            return 0;
        }
    }
    if (entryId != 0xFFFF && slot != 0xFF) {
        if (IsEntryFlagSet_0208696c(entryId, slot)) {
            return 2;
        }
        return 1;
    }
    return 2;
}
