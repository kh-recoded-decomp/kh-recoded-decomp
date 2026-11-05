#include "nitro/types.h"

extern u32 GetSceneTagTracker(void);
extern u32 FindActiveRecordById(u32 handle, int index);
extern void InvokeCallback40(u32 handle, u32 value);
extern u32 FindLoadedElementById(u32 handle, int index);
extern void SetTagRecordArmed(u32 handle, u32 value, int flag);

void DisarmAreaSequence1AndInvokeRecord5Callback(void) {
    u32 handle;
    u32 value;

    handle = GetSceneTagTracker();
    value = FindLoadedElementById(handle, 1);
    SetTagRecordArmed(handle, value, 0);
    value = FindActiveRecordById(handle, 5);
    InvokeCallback40(handle, value);
}
