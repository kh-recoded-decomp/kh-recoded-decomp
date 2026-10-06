#include "nitro/types.h"

typedef struct Session {
    u8 pad_0000[0x27f8];
    s8 unk_27F8;
} Session;

extern Session *data_ov001_020a0480;
extern BOOL func_ov001_020645c8(u32 flag);
extern u32 func_ov001_02063838(void);
extern u32 IsFieldTrackFlagSet(void);

BOOL func_ov001_0206e2d0(void)
{
    BOOL result = TRUE;

    if (func_ov001_020645c8(0x3308) != 0 || func_ov001_020645c8(0x35e5) != 0 ||
        func_ov001_02063838() != 0 || data_ov001_020a0480->unk_27F8 == 1 ||
        IsFieldTrackFlagSet() != 0) {
        result = FALSE;
    }
    return result;
}
