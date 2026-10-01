#include "nitro/types.h"

typedef u64 OSTick;

typedef struct FadeTween {
    u8 active;
    s8 busy;
    u8 pad_02[2];
    u32 startMilliseconds;
    u8 tween[0x18];
    u32 lowFlags : 2;
    u32 finished : 1;
    u32 highFlags : 29;
} FadeTween;

extern FadeTween *NNSi_FndGetCurrentRootHeap_0202a764(void);
extern void SampleTweenValue_0205258c(void *tween, s32 *value);
extern void SubScene9_StartFade_02066da4(BOOL fadeIn);
extern OSTick OS_GetTick_02003fd4(void);
extern void func_ov001_02066df4(s32 value);
extern void *func_ov001_02066d30(void);

void *StepFadeInTween_02066ce0(void)
{
    FadeTween *fade = NNSi_FndGetCurrentRootHeap_0202a764();
    void *next = NULL;
    s32 value;

    SampleTweenValue_0205258c(fade->tween, &value);
    if (fade->finished) {
        SubScene9_StartFade_02066da4(FALSE);
        value = 0x10000;
        fade->startMilliseconds = (OS_GetTick_02003fd4() * 64) / 0x82ea;
        next = func_ov001_02066d30;
    }
    func_ov001_02066df4(value);
    return next;
}
