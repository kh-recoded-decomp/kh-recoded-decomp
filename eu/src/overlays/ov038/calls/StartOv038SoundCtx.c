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
extern SoundCtx *data_ov038_020bd160;
extern void *NNSi_FndGetCurrentRootHeap(void);
extern void func_02029f8c(int processor, int overlayId);
extern void BuildCompletionStats(void);
extern void *func_ov038_020bbcb0(void);
extern void SetPanelEnabled(int value);
extern u32 RunOv038SoundCtxStates(void);

void *StartOv038SoundCtx(SoundCtxArgs *args)
{
    data_ov038_020bd160 = NNSi_FndGetCurrentRootHeap();
    data_ov038_020bd160->channel = args->channel;
    data_ov038_020bd160->paramA = args->paramA;
    data_ov038_020bd160->paramB = args->paramB;
    data_ov038_020bd160->flags = 0x23;
    data_ov038_020bd160->mode = args->mode;
    data_ov038_020bd160->state = 0;
    func_02029f8c(0, (int)OVERLAY_27_ID);
    BuildCompletionStats();
    func_ov038_020bbcb0();
    SetPanelEnabled(0);
    return RunOv038SoundCtxStates;
}
