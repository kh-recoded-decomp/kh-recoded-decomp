#include "nitro/types.h"

typedef struct InputRecord {
    u16 x;
    u16 y;
    u16 touch;
    u16 invalid;
} InputRecord;

extern InputRecord *data_ov027_020ba3c0;
extern int CopyRecentInputRecords_0202b6d0(InputRecord *records);
extern void func_01ff89a8(const void *src, void *dst, u32 size);

void CaptureLatestOnScreenTouch_020b9ef4(void)
{
    InputRecord records[4];
    int count;
    int i;
    int last;

    count = CopyRecentInputRecords_0202b6d0(records);
    last = count - 1;
    for (i = last; i >= 0; i--) {
        if (records[i].invalid == 0 && records[i].x < 256 && records[i].y < 192) {
            func_01ff89a8(&records[i], data_ov027_020ba3c0, sizeof(InputRecord));
            return;
        }
    }
    if (count >= 1) {
        func_01ff89a8(&records[last], data_ov027_020ba3c0, sizeof(InputRecord));
    }
}
