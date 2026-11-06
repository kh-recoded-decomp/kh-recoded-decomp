#include "nitro/types.h"

typedef struct {
    s8 mode;
    s8 channel;
    s16 paramA;
    s16 paramB;
} SoundCtxArgs;

typedef struct {
    s16 channel;
    s16 paramA;
    s16 paramB;
    u16 flags;
    s8 mode;
    u8 pad_09[0x0b];
    s32 state;
} SoundCtx;

extern char OVERLAY_27_ID[];
extern SoundCtx *gResultsPageOuterTaskWork;
extern void *GetRunningTaskWork(void);
extern void LoadOverlayAfterGeometryTransfer(int processor, int overlayId);
extern void BuildCompletionStats(void);
extern void *SetupResultsPageDisplay(void);
extern void SetPanelEnabled(int value);
extern u32 RunOv038SoundCtxStates(void);

void *StartOv038SoundCtx(SoundCtxArgs *args)
{
    gResultsPageOuterTaskWork = GetRunningTaskWork();
    gResultsPageOuterTaskWork->channel = args->channel;
    gResultsPageOuterTaskWork->paramA = args->paramA;
    gResultsPageOuterTaskWork->paramB = args->paramB;
    gResultsPageOuterTaskWork->flags = 0x23;
    gResultsPageOuterTaskWork->mode = args->mode;
    gResultsPageOuterTaskWork->state = 0;
    LoadOverlayAfterGeometryTransfer(0, (int)OVERLAY_27_ID);
    BuildCompletionStats();
    SetupResultsPageDisplay();
    SetPanelEnabled(0);
    return RunOv038SoundCtxStates;
}
