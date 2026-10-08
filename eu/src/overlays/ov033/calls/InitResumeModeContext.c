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

extern ResumeModeContext *data_ov033_020baae0;
extern char OVERLAY_104_ID[];
extern ResumeModeContext *NNSi_FndGetCurrentRootHeap(void);
extern void func_02029f8c(int processor, int overlayId);
extern void func_02029fac(int processor, int overlayId);
extern s32 __DSProt_DetectNotEmulator(void *task, void *callback, int arg);
extern s32 __DSProt_DetectDummy(void *task, void *callback, int arg);
extern s32 __DSProt_DetectNotFlashcart(void *task, void *callback, int arg);
extern u32 func_ov033_020ba400(void (*callback)(void));
extern void LoadActorOverlay(void);
extern void MI_CpuFill8(void *dst, u8 value, u32 size);
extern void SetupResumeDisplay(void);
extern u32 func_ov033_020ba574(void);

void *InitResumeModeContext(ResumeModeParams *params)
{
    void *setter;
    BOOL failed;

    data_ov033_020baae0 = NNSi_FndGetCurrentRootHeap();
    func_02029f8c(0, (int)OVERLAY_104_ID);
    setter = NULL;
    failed = __DSProt_DetectNotEmulator(func_ov033_020ba400, setter, 0) == ~(u32)setter;
    if (failed) {
        failed = __DSProt_DetectDummy(func_ov033_020ba400, setter, 0) == ~(u32)setter;
        if (failed) {
            MI_CpuFill8(&data_ov033_020baae0->state, 0xff, 4);
        } else {
            setter = LoadActorOverlay;
            failed = __DSProt_DetectNotFlashcart(func_ov033_020ba400, setter, 0) == ~(u32)setter;
            if (failed) {
                data_ov033_020baae0->active = 1;
            }
        }
    }
    func_02029fac(0, (int)OVERLAY_104_ID);
    data_ov033_020baae0->areaId = params->areaId;
    data_ov033_020baae0->posX = params->posX;
    data_ov033_020baae0->posY = params->posY;
    data_ov033_020baae0->modeId = params->modeId;
    data_ov033_020baae0->active = 1;
    data_ov033_020baae0->flags = 3;
    SetupResumeDisplay();
    data_ov033_020baae0->state = 0;
    return func_ov033_020ba574;
}
