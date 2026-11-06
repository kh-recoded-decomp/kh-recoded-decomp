#include "nitro/types.h"

extern u32 gArrowPromptWork;
extern u32 GetSceneTagTracker(void);
extern u32 GetTaskUpdateCount(void);
extern u32 FindActiveRecordById(u32 handle, u32 tag);
extern void TagTracker_InvokeCallback(u32 handle, u32 value);
extern void ShowTwoDigitCounters(void *context);

void StartArrowPromptTimedCounters(u32 param, u8 flag)
{
    u8 *context;
    u32 handle;
    u32 value;

    context = (u8 *)gArrowPromptWork;
    handle = GetSceneTagTracker();
    context[0] = 0;
    context[1] = flag;
    value = GetTaskUpdateCount();
    *(u32 *)(context + 0x10) = value;
    *(u32 *)(context + 0x18) = 0;
    *(u32 *)(context + 0x1c) = param;
    value = FindActiveRecordById(handle, 0x12e);
    TagTracker_InvokeCallback(handle, value);
    ShowTwoDigitCounters(context);
    *(u32 *)(context + 8) = 1;
}
