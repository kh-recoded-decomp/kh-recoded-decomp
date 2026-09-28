#include "nitro/types.h"

extern u32 g_ov038Context_020bd144;
extern void func_02029e7c(s32 value);
extern void func_02029ed0(s32 value);
extern void StopSoundStreamAtIndex_0204deb0(int handleIndex, int fadeFrame);
extern void ResetOv038ExitState_020bb638(u32 mode);

u32 AdvanceOv038ExitTimer_020babb4(void)
{
    u32 context;
    s32 tick;

    context = g_ov038Context_020bd144;
    tick = *(s32 *)(context + 0xd0a8);
    func_02029e7c(-tick);
    func_02029ed0(-tick);
    if (*(s32 *)(context + 0xd0a8) == 0) {
        StopSoundStreamAtIndex_0204deb0(0, 0x10);
    }
    tick = *(s32 *)(context + 0xd0a8) + 1;
    *(s32 *)(context + 0xd0a8) = tick;
    if (0x10 < tick) {
        ResetOv038ExitState_020bb638(4);
    }
    return 0;
}
