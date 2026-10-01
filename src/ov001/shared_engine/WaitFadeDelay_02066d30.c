#include "nitro/types.h"

typedef struct FadeDelay {
    u32 unk_00;
    int startMilliseconds;
} FadeDelay;

extern FadeDelay *NNSi_FndGetCurrentRootHeap_0202a764(void);
extern u64 func_02003fd4(void);
extern u64 func_02023d54(u64 dividend, u64 divisor);
extern void func_ov001_02066df4(s32 value);
extern void *StepFadeTween_02066d70(void);

void *WaitFadeDelay_02066d30(void)
{
    FadeDelay *fade = NNSi_FndGetCurrentRootHeap_0202a764();
    void *next = NULL;

    if (fade->startMilliseconds + 100 < func_02023d54(func_02003fd4() * 64, 0x82ea)) {
        next = StepFadeTween_02066d70;
    }
    func_ov001_02066df4(0x10000);
    return next;
}
