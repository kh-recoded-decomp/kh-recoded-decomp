#include "nitro/types.h"

extern int data_ov013_02074ce0;
extern void SetBrightnessAndSyncMain(int value);
extern void PostPanelEventOff(int mode, int value);
extern void func_ov013_0206caa4(void);
extern void DrawPlayerCardDetails(void);

/* Resets the panel cycle and advances the day. */
void func_ov013_0207390c(void) {
    *(int *)(data_ov013_02074ce0 + 0x2bc) = 0;
    SetBrightnessAndSyncMain(0xfffffff0);
    PostPanelEventOff(1, 0x6000);
    func_ov013_0206caa4();
    DrawPlayerCardDetails();
}
