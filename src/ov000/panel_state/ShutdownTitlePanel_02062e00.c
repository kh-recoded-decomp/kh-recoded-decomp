#include "nitro/types.h"

typedef struct {
    u8 pad_00[0x6680];
    s32 displayReady;
    u8 pad_6684[0x66a8 - 0x6684];
    void (*exitCallback)(void);
} Panel;

extern char OverlayId22_00000016[];

extern void SetupDisplayBanksAndLayers_0206141c(Panel *panel);
extern void func_02029f98(int processor, int overlayId);

void ShutdownTitlePanel_02062e00(Panel *panel)
{
    if (panel->displayReady == 0) {
        SetupDisplayBanksAndLayers_0206141c(panel);
    }
    panel->exitCallback();
    func_02029f98(0, (int)OverlayId22_00000016);
}

