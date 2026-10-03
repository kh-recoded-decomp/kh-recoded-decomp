#include "nitro/types.h"

typedef struct CapacityTable {
    s32 limits[4];
} CapacityTable;

typedef struct ProgressData {
    u8 pad_00[4];
    u16 unlockIds[3];
    u16 recordCount;
} ProgressData;

extern const CapacityTable data_ov076_020cd110;

extern u32 ReadSessionPackedBits_02064574(int bitOffset, u32 bitCount);
extern ProgressData *func_020505a8(void);
extern s8 GetCtxModeByte_02068084(void);
extern BOOL func_ov001_020645c8(u32 value);

BOOL IsRecordCapacityReached_020caa44(void)
{
    CapacityTable table = data_ov076_020cd110;
    u32 sessionState = ReadSessionPackedBits_02064574(0x1a00, 2);
    ProgressData *progress = func_020505a8();
    int i;

    if (GetCtxModeByte_02068084() == 5 && sessionState != 2) {
        if (!func_ov001_020645c8(0x3609) || !func_ov001_020645c8(0x360a)) {
            return TRUE;
        }
        if (progress->recordCount >= 0xce4) {
            return TRUE;
        }
        return FALSE;
    }
    for (i = 0; i < 3; i++) {
        if (progress->unlockIds[i] == 0xffff) {
            break;
        }
    }
    if (progress->recordCount >= table.limits[i]) {
        return TRUE;
    }
    return FALSE;
}
