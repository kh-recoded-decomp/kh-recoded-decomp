#include "nitro/types.h"

extern u32 gPanelCameraGlobalStorage;

extern void VEC_Subtract();
extern u32 CommitPanelProjectionAndViewAxes();
extern void SetSoundListenerFrame();

void CommitPanelCameraFrame(BOOL shouldBlend)
{
    u32 panel;
    u8 blended[12];

    panel = gPanelCameraGlobalStorage;
    if ((*(u32 *)(gPanelCameraGlobalStorage + 0x38) & 2) == 0) {
        if (shouldBlend) {
            VEC_Subtract(gPanelCameraGlobalStorage + 0x14, gPanelCameraGlobalStorage + 0x20, blended);
            SetSoundListenerFrame(panel + 0x20, blended, panel + 0x2c);
        }
        CommitPanelProjectionAndViewAxes(panel);
    }
}
