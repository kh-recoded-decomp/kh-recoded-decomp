#include "nitro/fx_types.h"
#pragma opt_propagation off

typedef struct ScrollPanel {
    int state;
    u8 reserved004[0x1c - 4];
    VecFx32 positions[2];
    u8 reserved034[0xf0 - 0x34];
    int timer;
    u8 reserved0f4[0x160 - 0xf4];
    u32 resourceId;
    int transitionValue164;
    int layoutMode;
    int transitionValue16c;
    u8 reserved170[0x18c - 0x170];
    fx32 baseX;
    fx32 baseY;
    VecFx32 *targetPosition;
} ScrollPanel;

extern ScrollPanel *data_ov001_020a04cc;
extern void ApplyVerticalLayoutOffset_0207d5f4(BOOL raised);
extern u32 func_ov001_02063b68(int index);

BOOL StartPanelLayoutTransition_0207d210(int layoutMode)
{
    ScrollPanel *panel = data_ov001_020a04cc;
    u32 resourceId;
    if (panel != NULL) {
        if (layoutMode == 0) {
            panel->baseX = 0xc000;
            panel->baseY = 0x13000;
        } else {
            ApplyVerticalLayoutOffset_0207d5f4(FALSE);
        }
        if (layoutMode == 0) {
            resourceId = func_ov001_02063b68(0);
        } else {
            resourceId = func_ov001_02063b68(1);
        }
        panel->resourceId = resourceId;
        panel->transitionValue164 = 0;
        panel->transitionValue16c = 0;
        panel->targetPosition = layoutMode == 0 ? &panel->positions[0] : &panel->positions[1];
        panel->layoutMode = layoutMode;
        panel->state = 2;
        panel->timer = 0;
    }
    return panel != NULL;
}
