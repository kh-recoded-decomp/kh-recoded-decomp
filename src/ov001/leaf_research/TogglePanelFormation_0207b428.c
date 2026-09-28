#include "nitro/types.h"

typedef struct {
    u8 pad_000[0x103];
    u8 formationType;
} PanelScene;

extern PanelScene *g_panelScene_020a04c8;

extern BOOL func_ov001_0207a8fc(PanelScene *panel);
extern void ApplyFormationSlots_020b6d90(int formationType);

void TogglePanelFormation_0207b428(void)
{
    PanelScene *panel = g_panelScene_020a04c8;

    if (panel->formationType == 1) {
        panel->formationType = 2;
    } else {
        panel->formationType = 1;
    }
    if (func_ov001_0207a8fc(panel)) {
        ApplyFormationSlots_020b6d90(panel->formationType);
    }
}
