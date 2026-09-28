#include "nitro/types.h"

typedef struct {
    u32 active;
    u8 modeState[8];
    s32 mode;
} ModeContext;

extern ModeContext *g_activeContext_020a04c4;

extern void *GetSceneTagTracker_020711b0(void);
extern void func_ov001_02079490(void *modeState, int value, int layer);
extern void func_ov001_0207942c(void *modeState);
extern void *func_ov027_020b8390(void *tracker, u32 id);
extern void func_ov027_020b83e8(void *tracker, void *entry, u32 flag);

void CloseActiveMode_0207a820(void)
{
    ModeContext *context = g_activeContext_020a04c4;
    void *tracker = GetSceneTagTracker_020711b0();

    func_ov001_02079490(context->modeState, 0, 9);
    func_ov001_02079490(context->modeState, 0, 10);
    func_ov001_02079490(context->modeState, 0, 11);
    func_ov001_0207942c(context->modeState);
    *(vu32 *)0x04000000 &= 0xffff1fff;
    func_ov027_020b83e8(tracker, func_ov027_020b8390(tracker, 5), 0);
    context->active = 0;
    context->mode = 0;
}
