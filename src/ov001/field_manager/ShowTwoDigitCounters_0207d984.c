#include "nitro/types.h"

typedef struct TwoDigitValues {
    u8 first;
    u8 second;
} TwoDigitValues;

extern void *GetSceneTagTracker_020711b0(void);
extern void *FindActiveRecordById_020b8184(void *pool, u16 recordId);
extern void func_ov027_020b81d8(void *pool, void *record, int frame);
extern void TagTracker_InvokeCallback_020b8210(void *tracker, void *record);

void ShowTwoDigitCounters_0207d984(TwoDigitValues *values)
{
    void *tracker = GetSceneTagTracker_020711b0();
    void *record;
    int tens;

    tens = values->first / 10;
    if (tens != 0) {
        record = FindActiveRecordById_020b8184(tracker, tens + 0x154);
        func_ov027_020b81d8(tracker, record, 1);
        TagTracker_InvokeCallback_020b8210(tracker, record);
    }
    record = FindActiveRecordById_020b8184(tracker, values->first % 10 + 0x154);
    func_ov027_020b81d8(tracker, record, 3);
    TagTracker_InvokeCallback_020b8210(tracker, record);
    TagTracker_InvokeCallback_020b8210(tracker, FindActiveRecordById_020b8184(tracker, 0x150));
    tens = values->second / 10;
    if (tens != 0) {
        record = FindActiveRecordById_020b8184(tracker, tens + 0x15e);
        func_ov027_020b81d8(tracker, record, 6);
        TagTracker_InvokeCallback_020b8210(tracker, record);
    }
    record = FindActiveRecordById_020b8184(tracker, values->second % 10 + 0x15e);
    func_ov027_020b81d8(tracker, record, 7);
    TagTracker_InvokeCallback_020b8210(tracker, record);
}
