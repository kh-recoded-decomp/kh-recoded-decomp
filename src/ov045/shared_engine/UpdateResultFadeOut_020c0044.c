#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct {
    u8 pad00[0x18];
    u32 unused0 : 2;
    u32 finished : 1;
} Tween;

typedef struct {
    u8 pad00[0x10];
    s16 phase;
    u8 pad12[6];
    BOOL started;
    u8 pad1c[0x18];
    void *pool;
    u8 pad38[0x19f8];
    Tween fade;
} ResultScreen;

extern ResultScreen *data_ov045_020c0880;
extern u16 data_02060500;

extern void InvokeCallbackForRecordId_020bf0c4(void *pool, u32 recordId);
extern void PlaySoundChecked_0204d8d0(void *ptr, int arg);
extern BOOL PlaySoundEffect_0204d924(int seqArcNo, int index);
extern void func_02052514(Tween *tween, int mode, fx32 startValue, fx32 endValue, int duration);
extern void func_0205255c(Tween *tween);
extern void SampleTweenValue_0205258c(Tween *tween_state, s32 *output_value);
extern void SetBrightnessAndSyncMain_02029e7c(int value);
extern void SetSecondaryBrightness_02029ed0(int value);
extern void *func_ov001_0207123c(void);
extern void ClearTileTableRowAndMarkDirty_020b9d18(void *table, int id);

int UpdateResultFadeOut_020c0044(void)
{
    ResultScreen *screen = data_ov045_020c0880;
    s32 brightness;

    if (screen->phase < 0) {
        return 0;
    }
    switch (screen->phase) {
    case 0:
        if (!screen->started) {
            InvokeCallbackForRecordId_020bf0c4(screen->pool, 0x10f);
            PlaySoundChecked_0204d8d0(NULL, 0x12);
            screen->started = TRUE;
            break;
        }
        if (!(data_02060500 & 0x2f0f)) {
            break;
        }
        PlaySoundEffect_0204d924(0, 1);
        screen->started = FALSE;
        screen->phase++;
        /* Fall through to start the fade. */
    case 1:
        if (!screen->started) {
            screen->started = TRUE;
            func_02052514(&screen->fade, 0, 0, -0x10000, 1000);
            func_0205255c(&screen->fade);
        }
        SampleTweenValue_0205258c(&screen->fade, &brightness);
        brightness /= 0x1000;
        SetBrightnessAndSyncMain_02029e7c(brightness);
        SetSecondaryBrightness_02029ed0(brightness);
        if (screen->fade.finished) {
            screen->started = FALSE;
            screen->phase = -1;
            ClearTileTableRowAndMarkDirty_020b9d18(func_ov001_0207123c(), 0xb);
        }
        break;
    }
    return 0;
}

