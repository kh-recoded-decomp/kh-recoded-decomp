#include "nitro/types.h"

typedef struct ResumeModeContext {
    s16 areaId;
    s16 posX;
    s16 posY;
    u16 flags;
    s32 modeId;
    s32 active;
    u8 pad_10[4];
    s32 state;
} ResumeModeContext;

typedef struct ResumeModeParams {
    s8 fadeMode;
    s8 areaId;
    s16 posX;
    s16 posY;
    u8 pad_06[2];
    s32 modeId;
} ResumeModeParams;

extern ResumeModeContext *gResumeModeWorkStorage;
extern char OVERLAY_104_ID[];
extern ResumeModeContext *GetRunningTaskWork(void);
extern void LoadOverlayAfterGeometryTransfer(int processor, int overlayId);
extern void UnloadOverlayAfterGeometryTransfer(int processor, int overlayId);
extern s32 __DSProt_DetectNotEmulator(void *task, void *callback, int arg);
extern s32 __DSProt_DetectDummy(void *task, void *callback, int arg);
extern s32 __DSProt_DetectNotFlashcart(void *task, void *callback, int arg);
extern u32 InvokeProtectionCallbackAndInvertAddress(void (*callback)(void));
extern void LoadActorOverlay(void);
extern void MI_CpuFill8(void *dst, u8 value, u32 size);
extern void SetupResumeDisplay(void);
extern u32 RunResumeModeStateMachine(void);

void *InitResumeModeContext(ResumeModeParams *params)
{
    void *setter;
    BOOL failed;

    gResumeModeWorkStorage = GetRunningTaskWork();
    LoadOverlayAfterGeometryTransfer(0, (int)OVERLAY_104_ID);
    setter = NULL;
    failed = __DSProt_DetectNotEmulator(InvokeProtectionCallbackAndInvertAddress, setter, 0) == ~(u32)setter;
    if (failed) {
        failed = __DSProt_DetectDummy(InvokeProtectionCallbackAndInvertAddress, setter, 0) == ~(u32)setter;
        if (failed) {
            MI_CpuFill8(&gResumeModeWorkStorage->state, 0xff, 4);
        } else {
            setter = LoadActorOverlay;
            failed = __DSProt_DetectNotFlashcart(InvokeProtectionCallbackAndInvertAddress, setter, 0) == ~(u32)setter;
            if (failed) {
                gResumeModeWorkStorage->active = 1;
            }
        }
    }
    UnloadOverlayAfterGeometryTransfer(0, (int)OVERLAY_104_ID);
    gResumeModeWorkStorage->areaId = params->areaId;
    gResumeModeWorkStorage->posX = params->posX;
    gResumeModeWorkStorage->posY = params->posY;
    gResumeModeWorkStorage->modeId = params->modeId;
    gResumeModeWorkStorage->active = 1;
    gResumeModeWorkStorage->flags = 3;
    SetupResumeDisplay();
    gResumeModeWorkStorage->state = 0;
    return RunResumeModeStateMachine;
}
