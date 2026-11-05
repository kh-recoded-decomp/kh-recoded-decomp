#include "nitro/types.h"

extern u32 data_ov001_020a04f4;
extern u32 GetSceneTagTracker(void);
extern void HideArrowPromptTimedCounters(void);
extern u32 FindActiveRecordById(u32 handle, u32 tag);
extern void InvokeCallback40(u32 handle, u32 value);

void StopFieldMinigameRound(void)
{
    u32 handle;
    u32 value;

    handle = GetSceneTagTracker();
    HideArrowPromptTimedCounters();
    value = FindActiveRecordById(handle, 0x12e);
    InvokeCallback40(handle, value);
    *(u32 *)(data_ov001_020a04f4 + 0x20) = 0;
}
