#include "nitro/types.h"

typedef struct RecordEntry {
    u8 pad_00[0x8];
    u16 flags;
} RecordEntry;

typedef struct RecordUser {
    u8 pad_00[0x38];
    u8 recordIndex;
} RecordUser;

extern RecordEntry *GetRecordEntry_02036810(int index);
extern void ApplyRecordTableEntry_020359f8(int index, int param2, int param3);
extern void SetRecordUserState_02082714(RecordUser *user, int state);

void ApplyRecordOrSetState_020822f8(RecordUser *user, BOOL enable)
{
    if (enable) {
        if (user->recordIndex != 0 && !(GetRecordEntry_02036810(user->recordIndex)->flags & 2)) {
            ApplyRecordTableEntry_020359f8(user->recordIndex, 0, 0);
        }
    } else {
        SetRecordUserState_02082714(user, 2);
    }
}
