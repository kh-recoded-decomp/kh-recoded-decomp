#include "nitro/types.h"

typedef struct {
    u8 pad_000[0x480];
    u32 unk_480_0 : 3;
    u32 restoreBrightness : 1;
    u32 isPaused : 1;
    u32 unk_480_5 : 9;
    u32 altMenu : 1;
} FieldManager;

typedef struct {
    u32 unk_00;
    FieldManager *manager;
} FieldManagerHandle;

extern FieldManagerHandle data_ov001_020a04a4;

extern void ResumeFieldFromPause_0207136c(void);
extern void ClosePanelAndResume_0202874c(void *panel);
extern void SelectActiveEntry_020011a4(int index);
extern void SetBrightnessAndSyncMain_02029e7c(int value);
extern void SetSecondaryBrightness_02029ed0(int value);
extern void SetAlternateMenuWidgets_020b61f4(int value);
extern u32 func_ov001_0207b3cc(void);
extern void ApplyScreenAlphaBlend_020b6e60(void);
extern void SetPanelReadyState_02028968(int a, int b);

BOOL ResumeFieldAfterPause_020704fc(void *panel) {
    if (!data_ov001_020a04a4.manager->isPaused) {
        return TRUE;
    }
    *(vu32 *)0x04000000 = (*(vu32 *)0x04000000 & ~0x1f00) | 0x100;
    ResumeFieldFromPause_0207136c();
    ClosePanelAndResume_0202874c(panel);
    SelectActiveEntry_020011a4(0);
    if (data_ov001_020a04a4.manager->restoreBrightness) {
        SetBrightnessAndSyncMain_02029e7c(0);
        SetSecondaryBrightness_02029ed0(0);
    }
    if (data_ov001_020a04a4.manager->altMenu) {
        SetAlternateMenuWidgets_020b61f4(0);
        data_ov001_020a04a4.manager->altMenu = 0;
    } else if (func_ov001_0207b3cc() == 0) {
        ApplyScreenAlphaBlend_020b6e60();
        SetPanelReadyState_02028968(0, 1);
    }
    data_ov001_020a04a4.manager->isPaused = 0;
    return TRUE;
}
