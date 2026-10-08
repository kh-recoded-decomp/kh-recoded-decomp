#include "nitro/types.h"

typedef struct Ov037Context {
    s16 state;
    u8 pad_02[0x1ce];
    s32 enabled;
    u8 pad_1d4[0x54];
    u64 startTick;
    u8 pad_230[0x04];
} Ov037Context;

extern Ov037Context *gContinueScreenContext;
extern char OVERLAY_27_ID[];
extern void func_02029f8c(int target, int overlayId);
extern void *NNSi_FndAllocFromDefaultHeap(u32 size);
extern void MI_CpuFill8(void *dst, int value, u32 size);
extern void SetupMainBgLayers(void);
extern void BuildMenuEntryList(void);
extern void func_ov037_020baedc(void);
extern void DrawMenuTexts(void);
extern void LoadMenuModelResources(void);
extern void ResetCameraProjectionOverrides(void);
extern u64 OS_GetTick(void);

void CreateOv037Context(void)
{
    if (gContinueScreenContext != NULL) {
        return;
    }
    func_02029f8c(0, (int)OVERLAY_27_ID);
    gContinueScreenContext = NNSi_FndAllocFromDefaultHeap(sizeof(Ov037Context));
    MI_CpuFill8(gContinueScreenContext, 0, sizeof(Ov037Context));
    gContinueScreenContext->state = 0;
    gContinueScreenContext->enabled = 1;
    SetupMainBgLayers();
    BuildMenuEntryList();
    func_ov037_020baedc();
    DrawMenuTexts();
    LoadMenuModelResources();
    ResetCameraProjectionOverrides();
    gContinueScreenContext->startTick = OS_GetTick();
}
