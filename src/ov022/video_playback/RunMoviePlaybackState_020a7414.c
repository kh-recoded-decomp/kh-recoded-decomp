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

extern MovieStateGlobals data_ov022_020b7d80;
extern u16 data_02060500;

extern MovieState *NNSi_FndGetCurrentRootHeap_0202a764(void);
extern BOOL TickSubtitleTimer_020a88c4(void);
extern BOOL func_ov022_020a73f4(void);
extern void func_02025cec(MovieLoader *loader);
extern u64 OS_GetTick_02003fd4(void);
extern void Pad_Sample_0202abc8(void);
extern void DrawMovieCaption_020a6f68(BOOL top);
extern BOOL ScriptVm_RunFrame_02025b18(MovieLoader *loader);
extern void GX_DispOff_02006640(void);
extern BOOL func_020109e4(int enable);
extern int func_02029f48(void);
extern int func_02029f58(void);
extern void SetBrightnessAndSyncMain_02029e7c(int brightness);
extern void SetSecondaryBrightness_02029ed0(int brightness);
extern void apply_pending_display_vram_mode_02006680(void);
extern void OS_WaitVBlankIntr_020049d0(void);
extern void StopMoviePlayback_020a8674(void);
extern void func_02004a60(int arg);
extern BOOL IsSoundStreamActive_0204ded4(int index);
extern void StopSoundStreamAtIndex_0204deb0(int index, int fadeFrames);
extern void func_020258f8(MovieLoader *loader);
extern void func_ov001_020631e4(s32 arg);
extern void UpdateMovieFadeOut_020a6ec0(MovieState *state);
extern void func_ov022_020a7790(void);

#define LID_STATUS (*(vu16 *)0x02ffffa8)

void *RunMoviePlaybackState_020a7414(void)
{
    MovieState *state = NNSi_FndGetCurrentRootHeap_0202a764();

    if (state->active == 0) {
        return NULL;
    }

    if (!(state->flags & 2) && state->phase == 2) {
        while (!TickSubtitleTimer_020a88c4()) {
            if (state->flags & 4) {
                if (func_ov022_020a73f4()) {
                    if (state->flags & 1) {
                        func_02025cec(&state->loader);
                    }
                    break;
                }
            } else if (state->lidClosed == 0 && (state->flags & 8)) {
                if ((OS_GetTick_02003fd4() - state->padTick) * 64 / 0x82ea <= 50) {
                    data_02060500 = 0;
                } else {
                    Pad_Sample_0202abc8();
                    state->padTick = OS_GetTick_02003fd4();
                }
                if (state->mode == 1) {
                    if (data_02060500 & 9) {
                        state->fadeLevel = 0;
                        state->flags |= 4;
                        data_ov022_020b7d80.skipRequested = 1;
                    }
                } else if (state->captionVisible == 0) {
                    if (data_02060500 & 8) {
                        state->captionVisible = 1;
                        DrawMovieCaption_020a6f68(FALSE);
                        state->captionDrawn = 1;
                        state->captionTick = OS_GetTick_02003fd4();
                    }
                } else {
                    if (data_02060500 & 8) {
                        state->fadeLevel = 0;
                        state->flags |= 4;
                        data_ov022_020b7d80.skipRequested = 1;
                    } else if ((OS_GetTick_02003fd4() - state->captionTick) * 64 / 0x82ea > 3000) {
                        state->captionVisible = 0;
                        DrawMovieCaption_020a6f68(FALSE);
                        state->captionDrawn = 1;
                    }
                }
            }

            if ((state->flags & 1) && !ScriptVm_RunFrame_02025b18(&state->loader)) {
                state->flags &= ~1;
            }

            if (state->lidClosed == 0 && ((LID_STATUS & 0x8000) >> 15)) {
                GX_DispOff_02006640();
                func_020109e4(0);
                state->lidClosed = 1;
            } else if (state->lidClosed != 0 && !((LID_STATUS & 0x8000) >> 15)) {
                if (func_020109e4(1)) {
                    state->lidClosed = 0;
                    SetBrightnessAndSyncMain_02029e7c(func_02029f48());
                    SetSecondaryBrightness_02029ed0(func_02029f58());
                    apply_pending_display_vram_mode_02006680();
                }
            }
        }

        if (state->flags & 4) {
            while (!func_ov022_020a73f4()) {
                OS_WaitVBlankIntr_020049d0();
            }
            if (state->flags & 1) {
                func_02025cec(&state->loader);
            }
        }
        StopMoviePlayback_020a8674();
        state->phase = 3;
        if (!(state->flags & 1)) {
            goto finish;
        }
        goto stillRunning;
    } else if (ScriptVm_RunFrame_02025b18(&state->loader)) {
    stillRunning:
        return NULL;
    }

finish:
    if (state->mode == 3) {
        func_02004a60(0);
    }
    if ((state->flags & 4) && IsSoundStreamActive_0204ded4(0)) {
        StopSoundStreamAtIndex_0204deb0(0, 20);
    }
    func_020258f8(&state->loader);
    switch (state->loader.exitAction) {
    case 1:
        func_ov001_020631e4(state->loader.exitArg);
    case 0:
    case 2:
        state->active = 2;
        break;
    }
    state->fadeLevel = 15;
    OS_WaitVBlankIntr_020049d0();
    UpdateMovieFadeOut_020a6ec0(state);
    SetBrightnessAndSyncMain_02029e7c(-16);
    SetSecondaryBrightness_02029ed0(-16);
    return func_ov022_020a7790;
}
