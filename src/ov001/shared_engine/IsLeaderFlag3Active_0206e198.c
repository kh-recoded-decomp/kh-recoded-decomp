#include "nitro/types.h"

typedef struct PartyState {
    u8 pad_00[0x28];
    u16 flags;
} PartyState;

extern PartyState *data_ov001_020a049c;
extern u32 GetBoundedEntryField_0206db5c(int index);

BOOL IsLeaderFlag3Active_0206e198(void)
{
    PartyState *party = data_ov001_020a049c;
    BOOL result = FALSE;

    if (party == NULL) {
        return result;
    }
    if (GetBoundedEntryField_0206db5c(0) != 0 && (party->flags & 8) > 0) {
        result = TRUE;
    }
    return result;
}
