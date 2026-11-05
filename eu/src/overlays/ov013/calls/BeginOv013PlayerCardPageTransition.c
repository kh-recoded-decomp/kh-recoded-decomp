#include "nitro/types.h"

extern int data_ov013_02074ce0;
extern void SetBrightnessAndSyncMain(int value);
extern void PostPanelEventOff(int mode, int value);
extern void ConfigureOv013PlayerCardPageMode(void);
extern void DrawPlayerCardDetails(void);

/* Starts the player-card page transition, then configures and draws its details. */
void BeginOv013PlayerCardPageTransition(void) {
    *(int *)(data_ov013_02074ce0 + 0x2bc) = 0;
    SetBrightnessAndSyncMain(0xfffffff0);
    PostPanelEventOff(1, 0x6000);
    ConfigureOv013PlayerCardPageMode();
    DrawPlayerCardDetails();
}
