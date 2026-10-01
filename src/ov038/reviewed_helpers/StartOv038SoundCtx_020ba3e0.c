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

extern char OVERLAY_27_ID_0000001b[];
extern SoundCtx *g_ov038SoundCtx_020bd140;
extern void *NNSi_FndGetCurrentRootHeap_0202a764(void);
extern void func_02029f78(int processor, int overlayId);
extern void func_ov038_020bb674(void);
extern void *PXI_Init_020bbc90(void);
extern void func_02025438(int value);
extern u32 RunOv038SoundCtxStates_020ba468(void);

void *StartOv038SoundCtx_020ba3e0(SoundCtxArgs *args)
{
    g_ov038SoundCtx_020bd140 = NNSi_FndGetCurrentRootHeap_0202a764();
    g_ov038SoundCtx_020bd140->channel = args->channel;
    g_ov038SoundCtx_020bd140->paramA = args->paramA;
    g_ov038SoundCtx_020bd140->paramB = args->paramB;
    g_ov038SoundCtx_020bd140->flags = 0x23;
    g_ov038SoundCtx_020bd140->mode = args->mode;
    g_ov038SoundCtx_020bd140->state = 0;
    func_02029f78(0, (int)OVERLAY_27_ID_0000001b);
    func_ov038_020bb674();
    PXI_Init_020bbc90();
    func_02025438(0);
    return RunOv038SoundCtxStates_020ba468;
}
