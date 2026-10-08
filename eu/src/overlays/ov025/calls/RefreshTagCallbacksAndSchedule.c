#include "nitro/types.h"

extern u32 data_ov025_020b7780;
extern char sOv025_Ocuitask_020b775c[];

extern u32 MakePrimaryVramKey(u32 id);
extern void func_ov027_020b7e44(u32 ctx, u32 id);
extern u32 FindActiveRecordById(u32 ctx, u32 id);
extern void func_ov027_020b8230(int *tracker, int arg);
extern void func_ov025_020b584c(u32 ctx);
extern void InvokeForChannelOrBoth(int kind, void *data, u32 handler, u32 duration);
extern void SetWidgetRootTouchEnabled(u32 ctx, u32 enable);

u32 RefreshTagCallbacksAndSchedule(void)
{
    u32 ctx = data_ov025_020b7780;
    u32 sound = MakePrimaryVramKey(0x6a);
    u32 tag;

    func_ov027_020b7e44(ctx, sound);
    tag = FindActiveRecordById(ctx, 0);
    func_ov027_020b8230((int *)ctx, tag);
    tag = FindActiveRecordById(ctx, 1);
    func_ov027_020b8230((int *)ctx, tag);
    func_ov025_020b584c(ctx);
    InvokeForChannelOrBoth(1, sOv025_Ocuitask_020b775c, 0x020b5821, 0xffffffff);
    SetWidgetRootTouchEnabled(ctx + 0x4c, 1);
    return 0x020b5f29;
}
