#include "nitro/types.h"


typedef struct {
    s16 areaId;
    s16 posX;
    s16 posY;
    u16 flags;
    s32 modeId;
    s32 active;
    u8 pad_10[4];
    s32 state;
} SoundCtx;

typedef struct {
    s8 fadeMode;
    s8 areaId;
    s16 posX;
    s16 posY;
    u8 pad_06[2];
    s32 modeId;
} ResumeParams;

extern SoundCtx *g_ov038SoundCtx_020baac0;
extern char OverlayId104_00000068[];
extern SoundCtx *NNSi_FndGetCurrentRootHeap_0202a764(void);
extern void func_02029f78(int processor, int overlayId);
extern void func_02029f98(int processor, int overlayId);
extern s32 func_ov104_020d1f54(void *task, void *callback, int arg);
extern s32 func_ov104_020d1f90(void *task, void *callback, int arg);
extern s32 func_ov104_020d1edc(void *task, void *callback, int arg);
extern u32 func_ov033_020ba3e0(void (*callback)(void));
extern void LoadActorOverlay_020ba3f8(void);
extern void func_01ff8830(void *dst, u8 value, u32 size);
extern void SetupResumeDisplay_020ba7d8(void);
extern u32 func_ov033_020ba554(void);

void *InitResumeModeContext_020ba410(ResumeParams *params)
{
    void *setter;
    BOOL failed;

    g_ov038SoundCtx_020baac0 = NNSi_FndGetCurrentRootHeap_0202a764();
    func_02029f78(0, (int)OverlayId104_00000068);
    setter = NULL;
    failed = func_ov104_020d1f54(func_ov033_020ba3e0, setter, 0) == ~(u32)setter;
    if (failed) {
        failed = func_ov104_020d1f90(func_ov033_020ba3e0, setter, 0) == ~(u32)setter;
        if (failed) {
            func_01ff8830(&g_ov038SoundCtx_020baac0->state, 0xff, 4);
        } else {
            setter = LoadActorOverlay_020ba3f8;
            failed = func_ov104_020d1edc(func_ov033_020ba3e0, setter, 0) == ~(u32)setter;
            if (failed) {
                g_ov038SoundCtx_020baac0->active = 1;
            }
        }
    }
    func_02029f98(0, (int)OverlayId104_00000068);
    g_ov038SoundCtx_020baac0->areaId = params->areaId;
    g_ov038SoundCtx_020baac0->posX = params->posX;
    g_ov038SoundCtx_020baac0->posY = params->posY;
    g_ov038SoundCtx_020baac0->modeId = params->modeId;
    g_ov038SoundCtx_020baac0->active = 1;
    g_ov038SoundCtx_020baac0->flags = 3;
    SetupResumeDisplay_020ba7d8();
    g_ov038SoundCtx_020baac0->state = 0;
    return func_ov033_020ba554;
}
