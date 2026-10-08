#include "nitro/types.h"

typedef struct MovieLoader {
    u8 pad_000[0x1cc];
    s32 exitAction;
    s32 exitArg;
    u8 pad_1D4[0x474];
} MovieLoader;

typedef struct MovieState {
    u16 active;
    u16 flags;
    MovieLoader loader;
    u8 pad_64C[0x264];
    s32 phase;
    u8 lidClosed;
    u8 captionDrawn;
    u8 pad_8B6[0x2];
    s32 fadeLevel;
    s32 captionVisible;
    u8 pad_8C0[0x200];
    u64 padTick;
    u64 captionTick;
    s32 mode;
} MovieState;

typedef struct MovieStateGlobals {
    MovieState *state;
    s32 skipRequested;
} MovieStateGlobals;

extern MovieStateGlobals data_ov022_020b7da0;
extern u16 data_02060500;

extern MovieState *NNSi_FndGetCurrentRootHeap(void);
extern BOOL TickSubtitleTimer(void);
extern BOOL func_ov022_020a7414(void);
extern void MarkPendingActionIfTargetSet(MovieLoader *loader);
extern u64 OS_GetTick(void);
extern void Pad_Sample(void);
extern void DrawMovieCaption(BOOL top);
extern BOOL ScriptVm_RunFrame(MovieLoader *loader);
extern void GX_DispOff(void);
extern BOOL PM_SetLCDPower(int enable);
extern int func_02029f5c(void);
extern int func_02029f6c(void);
extern void SetBrightnessAndSyncMain(int brightness);
extern void SetSecondaryBrightness(int brightness);
extern void GX_DispOn(void);
extern void OS_WaitVBlankIntr(void);
extern void StopMoviePlayback(void);
extern void OS_ResetSystem(int arg);
extern BOOL IsSoundStreamActive(int index);
extern void StopSoundStreamAtIndex(int index, int fadeFrames);
extern void PcmChannel_ResetAndEnable(MovieLoader *loader);
extern void SetPendingFieldValue(s32 arg);
extern void UpdateMovieFadeOut(MovieState *state);
extern void func_ov022_020a77b0(void);

#define LID_STATUS (*(vu16 *)0x02ffffa8)

void *RunMoviePlaybackState(void)
{
    MovieState *state = NNSi_FndGetCurrentRootHeap();

    if (state->active == 0) {
        return NULL;
    }

    if (!(state->flags & 2) && state->phase == 2) {
        while (!TickSubtitleTimer()) {
            if (state->flags & 4) {
                if (func_ov022_020a7414()) {
                    if (state->flags & 1) {
                        MarkPendingActionIfTargetSet(&state->loader);
                    }
                    break;
                }
            } else if (state->lidClosed == 0 && (state->flags & 8)) {
                if ((OS_GetTick() - state->padTick) * 64 / 0x82ea <= 50) {
                    data_02060500 = 0;
                } else {
                    Pad_Sample();
                    state->padTick = OS_GetTick();
                }
                if (state->mode == 1) {
                    if (data_02060500 & 9) {
                        state->fadeLevel = 0;
                        state->flags |= 4;
                        data_ov022_020b7da0.skipRequested = 1;
                    }
                } else if (state->captionVisible == 0) {
                    if (data_02060500 & 8) {
                        state->captionVisible = 1;
                        DrawMovieCaption(FALSE);
                        state->captionDrawn = 1;
                        state->captionTick = OS_GetTick();
                    }
                } else {
                    if (data_02060500 & 8) {
                        state->fadeLevel = 0;
                        state->flags |= 4;
                        data_ov022_020b7da0.skipRequested = 1;
                    } else if ((OS_GetTick() - state->captionTick) * 64 / 0x82ea > 3000) {
                        state->captionVisible = 0;
                        DrawMovieCaption(FALSE);
                        state->captionDrawn = 1;
                    }
                }
            }

            if ((state->flags & 1) && !ScriptVm_RunFrame(&state->loader)) {
                state->flags &= ~1;
            }

            if (state->lidClosed == 0 && ((LID_STATUS & 0x8000) >> 15)) {
                GX_DispOff();
                PM_SetLCDPower(0);
                state->lidClosed = 1;
            } else if (state->lidClosed != 0 && !((LID_STATUS & 0x8000) >> 15)) {
                if (PM_SetLCDPower(1)) {
                    state->lidClosed = 0;
                    SetBrightnessAndSyncMain(func_02029f5c());
                    SetSecondaryBrightness(func_02029f6c());
                    GX_DispOn();
                }
            }
        }

        if (state->flags & 4) {
            while (!func_ov022_020a7414()) {
                OS_WaitVBlankIntr();
            }
            if (state->flags & 1) {
                MarkPendingActionIfTargetSet(&state->loader);
            }
        }
        StopMoviePlayback();
        state->phase = 3;
        if (!(state->flags & 1)) {
            goto finish;
        }
        goto stillRunning;
    } else if (ScriptVm_RunFrame(&state->loader)) {
    stillRunning:
        return NULL;
    }

finish:
    if (state->mode == 3) {
        OS_ResetSystem(0);
    }
    if ((state->flags & 4) && IsSoundStreamActive(0)) {
        StopSoundStreamAtIndex(0, 20);
    }
    PcmChannel_ResetAndEnable(&state->loader);
    switch (state->loader.exitAction) {
    case 1:
        SetPendingFieldValue(state->loader.exitArg);
    case 0:
    case 2:
        state->active = 2;
        break;
    }
    state->fadeLevel = 15;
    OS_WaitVBlankIntr();
    UpdateMovieFadeOut(state);
    SetBrightnessAndSyncMain(-16);
    SetSecondaryBrightness(-16);
    return func_ov022_020a77b0;
}
