#include "nitro/types.h"

typedef struct StageObjectLoadState {
    u8 pad_00[0x44];
    u16 entryId;
    u8 entrySlot;
    u8 pad_47[6];
    s8 flagOffset;
    u8 pad_4e[6];
    u16 flags;
} StageObjectLoadState;

extern int GetEntryUnlockState_02087478(
    BOOL skipModeCheck, u32 flagOffset, u32 entryId, u32 slot);

int GetStageObjectLoadPhase_020a5248(StageObjectLoadState *object)
{
    BOOL skipModeCheck;

    if (object->flags & 0x200) {
        switch (object->flags & 0x400) {
        default:
            skipModeCheck = FALSE;
            break;
        case 0:
            skipModeCheck = TRUE;
            break;
        }
        if (GetEntryUnlockState_02087478(skipModeCheck, object->flagOffset,
                                object->entryId, object->entrySlot) == 0) {
            return 10;
        }
        return 1;
    }
    return 0;
}
