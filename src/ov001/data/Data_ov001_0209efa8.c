#include "nitro/types.h"

extern void DrawCounterHudParts_0207c174(void);
extern void RefreshCounterDigits_0207c1a8(void);
extern void RunLogoFadeSequence_0207cbb0(void);
extern void UpdateFadeSequence_0207d0b8(void);
extern void UpdateShortFadeSequence_0207d04c(void);
extern void func_ov001_0207ba8c(void);
extern void func_ov001_0207becc(void);
extern void func_ov001_0207c288(void);
extern void func_ov001_0207cc8c(void);

void (*data_ov001_0209efbc[6])(void) = {
    NULL,
    func_ov001_0207ba8c,
    func_ov001_0207becc,
    DrawCounterHudParts_0207c174,
    RefreshCounterDigits_0207c1a8,
    func_ov001_0207c288,
};

void (*data_ov001_0209efa8[5])(void) = {
    NULL,
    RunLogoFadeSequence_0207cbb0,
    func_ov001_0207cc8c,
    UpdateShortFadeSequence_0207d04c,
    UpdateFadeSequence_0207d0b8,
};
