#include "nitro/types.h"

typedef struct InputRecord {
    u16 x;
    u16 y;
    u16 touch;
    u16 invalid;
} InputRecord;

extern int CopyRecentInputRecords_0202b6d0(InputRecord *records);
extern void func_01ff89a8(const void *src, void *dst, u32 size);

BOOL GetLatestValidInputRecord_020b8774(void *root, InputRecord *out)
{
    InputRecord records[4];
    int count;
    int i;
    int last;

    count = CopyRecentInputRecords_0202b6d0(records);
    last = count - 1;

    for (i = last; i >= 0; i--) {
        if (records[i].invalid == 0) {
            func_01ff89a8(&records[i], out, sizeof(InputRecord));
            return TRUE;
        }
    }
    if (count >= 1) {
        func_01ff89a8(&records[last], out, sizeof(InputRecord));
    } else {
        return FALSE;
    }
    return TRUE;
}

