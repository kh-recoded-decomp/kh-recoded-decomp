#include "src/overlays/ov027/CapturedTouch.h"

extern int CopyRecentInputRecords(CapturedTouchRecord *records);
extern void MI_CpuCopy8(const void *src, void *dst, u32 size);

void CaptureLatestOnScreenTouch(void)
{
    CapturedTouchRecord records[4];
    int count;
    int i;
    int last;

    count = CopyRecentInputRecords(records);
    last = count - 1;
    for (i = last; i >= 0; i--) {
        if (records[i].invalid == 0 && records[i].x < 256 && records[i].y < 192) {
            MI_CpuCopy8(&records[i], gCapturedTouchRecord, sizeof(CapturedTouchRecord));
            return;
        }
    }
    if (count >= 1) {
        MI_CpuCopy8(&records[last], gCapturedTouchRecord, sizeof(CapturedTouchRecord));
    }
}
