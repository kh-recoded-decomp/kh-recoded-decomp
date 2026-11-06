#include "nitro/types.h"

extern u32 gMenuListWorkStorage;
extern char sOv025_Ocuitask_020b775c[];

extern u32 MakePrimaryVramKey(u32 id);
extern void LoadTagTrackerResourceFile(u32 ctx, u32 id);
extern u32 FindActiveRecordById(u32 ctx, u32 id);
extern void TagTracker_InvokeCallback(int *tracker, int arg);
extern void AdvanceMenuDelayCounter(u32 ctx);
extern void InvokeForChannelOrBoth(int kind, void *data, u32 handler, u32 duration);
extern void SetWidgetRootTouchEnabled(u32 ctx, u32 enable);

u32 RefreshTagCallbacksAndSchedule(void)
{
    u32 ctx = gMenuListWorkStorage;
    u32 sound = MakePrimaryVramKey(0x6a);
    u32 tag;

    LoadTagTrackerResourceFile(ctx, sound);
    tag = FindActiveRecordById(ctx, 0);
    TagTracker_InvokeCallback((int *)ctx, tag);
    tag = FindActiveRecordById(ctx, 1);
    TagTracker_InvokeCallback((int *)ctx, tag);
    AdvanceMenuDelayCounter(ctx);
    InvokeForChannelOrBoth(1, sOv025_Ocuitask_020b775c, 0x020b5821, 0xffffffff);
    SetWidgetRootTouchEnabled(ctx + 0x4c, 1);
    return 0x020b5f29;
}
