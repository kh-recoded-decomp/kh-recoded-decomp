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

extern void *NNSi_FndGetCurrentRootHeap(void);
extern u32 func_01ff80d4(void);
extern u64 OS_GetTick(void);
extern int TickSubtitleTimer(void);
extern int MovieScene_IsFadeDone(void);
extern void MarkPendingActionIfTargetSet(void *script);
extern int ScriptVm_RunFrame(void *script);
extern void MovieScene_ProcessTimeline(MovieRunScene *scene, int frame);
extern void GX_DispOff(void);
extern int PM_SetLCDPower(int power);
extern int func_02029f5c(void);
extern int func_02029f6c(void);
extern void SetBrightnessAndSyncMain(int value);
extern void SetSecondaryBrightness(int value);
extern void GX_DispOn(void);
extern void OS_WaitVBlankIntr(void);
extern void StopMoviePlayback(void);
extern BOOL PcmChannel_ResetAndEnable(void *script);
extern void MovieScene_RequestStop(void);

void *MovieScene_Run(void)
{
    MovieRunScene *scene;
    u32 prevCount;
    u32 count;
    u64 startTick;
    u16 buttons;
    u16 held;
    u32 skip;
    int exitScene;

    scene = NNSi_FndGetCurrentRootHeap();
    if ((scene->flags & 2) == 0 && (scene->field_8b0 == 2 || scene->streamActive == 2)) {
        prevCount = func_01ff80d4();
        startTick = OS_GetTick();
        if (TickSubtitleTimer() == 0) {
            do {
                if ((scene->flags & 4) != 0) {
                    if (MovieScene_IsFadeDone() != 0) {
                        if ((scene->flags & 1) != 0) {
                            MarkPendingActionIfTargetSet(scene->script);
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
                if ((scene->flags & 1) != 0 && ScriptVm_RunFrame(scene->script) == 0) {
                    scene->flags &= ~1;
                }
                count = func_01ff80d4();
                if (prevCount != count) {
                    MovieScene_ProcessTimeline(scene, (int)((OS_GetTick() - startTick) * 64 / 0x82ea * 0xbb5 / 100000) + 90);
                    prevCount = count;
                }
                if (scene->lcdOff == 0 && ((int)(*(vu16 *)0x02ffffa8 & 0x8000) >> 15) != 0) {
                    GX_DispOff();
                    PM_SetLCDPower(0);
                    scene->lcdOff = 1;
                } else if (scene->lcdOff != 0 && ((int)(*(vu16 *)0x02ffffa8 & 0x8000) >> 15) == 0 &&
                           PM_SetLCDPower(1) != 0) {
                    scene->lcdOff = 0;
                    SetBrightnessAndSyncMain(func_02029f5c());
                    SetSecondaryBrightness(func_02029f6c());
                    GX_DispOn();
                }
            } while (TickSubtitleTimer() == 0);
        }
        if ((scene->flags & 4) != 0) {
            while (MovieScene_IsFadeDone() == 0) {
                OS_WaitVBlankIntr();
            }
            if ((scene->flags & 1) != 0) {
                MarkPendingActionIfTargetSet(scene->script);
            }
        }
        StopMoviePlayback();
        scene->field_8b0 = scene->streamActive = 3;
        if ((scene->flags & 1) == 0) {
            goto finish;
        }
        goto keepRunning;
    }
    if (ScriptVm_RunFrame(scene->script) == 0) {
        goto finish;
    }

keepRunning:
    SetBrightnessAndSyncMain(-16);
    SetSecondaryBrightness(-16);
    return NULL;

finish:
    PcmChannel_ResetAndEnable(scene->script);
    exitScene = scene->exitScene;
    if (exitScene == 0 || (exitScene != 1 && exitScene == 2)) {
        scene->state = 2;
    }
    SetBrightnessAndSyncMain(-16);
    SetSecondaryBrightness(-16);
    return MovieScene_RequestStop;
}
