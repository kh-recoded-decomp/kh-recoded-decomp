#include "nitro/types.h"

typedef struct Session {
    u8 pad_0000[0x27f8];
    s8 unk_27F8;
} Session;

extern Session *data_ov001_020a0480;
extern BOOL IsSessionFlagSet(u32 flag);
extern u32 GetSessionFlagsMask20(void);
extern u32 IsFieldTrackFlagSet(void);

BOOL IsSlotItemUseRecoveryAllowed(void)
{
    BOOL result = TRUE;

    if (IsSessionFlagSet(0x3308) != 0 || IsSessionFlagSet(0x35e5) != 0 ||
        GetSessionFlagsMask20() != 0 || data_ov001_020a0480->unk_27F8 == 1 ||
        IsFieldTrackFlagSet() != 0) {
        result = FALSE;
    }
    return result;
}
