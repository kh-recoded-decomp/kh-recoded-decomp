#include "nitro/types.h"

typedef struct MovieRunScene {
    u16 state;
    u16 flags;
    u8 script[0x1cc];
    int exitScene;
    u8 pad_1d4[0x6dc];
    int field_8b0;
    int streamActive;
    u8 lcdOff;
    u8 pad_8b9[7];
    int fadeTarget;
    int skipHeld;
} MovieRunScene;

extern void *NNSi_FndGetCurrentRootHeap_0202a764(void);
extern u32 func_01ff80d4(void);
extern u64 OS_GetTick_02003fd4(void);
extern int func_ov022_020a88c4(void);
extern int MovieScene_IsFadeDone_02064008(void);
extern void func_02025cec(void *script);
extern int ScriptVm_RunFrame_02025b18(void *script);
extern void func_ov003_0206436c(MovieRunScene *scene, int frame);
extern void GX_DispOff_02006640(void);
extern int func_020109e4(int power);
extern int func_02029f48(void);
extern int func_02029f58(void);
extern void SetBrightnessAndSyncMain_02029e7c(int value);
extern void SetSecondaryBrightness_02029ed0(int value);
extern void apply_pending_display_vram_mode_02006680(void);
extern void OS_WaitVBlankIntr_020049d0(void);
extern void StopMoviePlayback_020a8674(void);
extern BOOL func_020258f8(void *script);
extern void MovieScene_RequestStop_020646e8(void);

void *MovieScene_Run_020643f0(void)
{
    MovieRunScene *scene;
    u32 prevCount;
    u32 count;
    u64 startTick;
    u16 buttons;
    u16 held;
    u32 skip;
    int exitScene;

    scene = NNSi_FndGetCurrentRootHeap_0202a764();
    if ((scene->flags & 2) == 0 && (scene->field_8b0 == 2 || scene->streamActive == 2)) {
        prevCount = func_01ff80d4();
        startTick = OS_GetTick_02003fd4();
        if (func_ov022_020a88c4() == 0) {
            do {
                if ((scene->flags & 4) != 0) {
                    if (MovieScene_IsFadeDone_02064008() != 0) {
                        if ((scene->flags & 1) != 0) {
                            func_02025cec(scene->script);
                        }
                        break;
                    }
                } else if (scene->lcdOff == 0) {
                    buttons = ((*(vu16 *)0x04000130 | *(vu16 *)0x02ffffa8) ^ 0x2fff) & 0x2fff;
                    held = buttons & ~((buttons & 0x40) << 1) & ~((buttons & 0x20) >> 1);
                    skip = held & 8;
                    if (scene->skipHeld == 0 && skip != 0) {
                        scene->fadeTarget = 0;
                        scene->flags |= 4;
                    }
                    scene->skipHeld = skip;
                }
                if ((scene->flags & 1) != 0 && ScriptVm_RunFrame_02025b18(scene->script) == 0) {
                    scene->flags &= ~1;
                }
                count = func_01ff80d4();
                if (prevCount != count) {
                    func_ov003_0206436c(scene, (int)((OS_GetTick_02003fd4() - startTick) * 64 / 0x82ea * 0xbb5 / 100000) + 90);
                    prevCount = count;
                }
                if (scene->lcdOff == 0 && ((int)(*(vu16 *)0x02ffffa8 & 0x8000) >> 15) != 0) {
                    GX_DispOff_02006640();
                    func_020109e4(0);
                    scene->lcdOff = 1;
                } else if (scene->lcdOff != 0 && ((int)(*(vu16 *)0x02ffffa8 & 0x8000) >> 15) == 0 &&
                           func_020109e4(1) != 0) {
                    scene->lcdOff = 0;
                    SetBrightnessAndSyncMain_02029e7c(func_02029f48());
                    SetSecondaryBrightness_02029ed0(func_02029f58());
                    apply_pending_display_vram_mode_02006680();
                }
            } while (func_ov022_020a88c4() == 0);
        }
        if ((scene->flags & 4) != 0) {
            while (MovieScene_IsFadeDone_02064008() == 0) {
                OS_WaitVBlankIntr_020049d0();
            }
            if ((scene->flags & 1) != 0) {
                func_02025cec(scene->script);
            }
        }
        StopMoviePlayback_020a8674();
        scene->field_8b0 = scene->streamActive = 3;
        if ((scene->flags & 1) == 0) {
            goto finish;
        }
        goto keepRunning;
    }
    if (ScriptVm_RunFrame_02025b18(scene->script) == 0) {
        goto finish;
    }

keepRunning:
    SetBrightnessAndSyncMain_02029e7c(-16);
    SetSecondaryBrightness_02029ed0(-16);
    return NULL;

finish:
    func_020258f8(scene->script);
    exitScene = scene->exitScene;
    if (exitScene == 0 || (exitScene != 1 && exitScene == 2)) {
        scene->state = 2;
    }
    SetBrightnessAndSyncMain_02029e7c(-16);
    SetSecondaryBrightness_02029ed0(-16);
    return MovieScene_RequestStop_020646e8;
}
