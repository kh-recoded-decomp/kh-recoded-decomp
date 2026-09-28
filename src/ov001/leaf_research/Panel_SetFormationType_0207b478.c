#include "nitro/types.h"

typedef struct Panel {
    u8 pad_000[0x103];
    u8 formationType;
} Panel;

extern Panel *g_activePanel_020a04c8;
extern u32 func_ov001_0207a8fc(Panel *panel);
extern void ApplyFormationSlots_020b6d90(int formationType);

void Panel_SetFormationType_0207b478(int formationType)
{
    Panel *panel;

    panel = g_activePanel_020a04c8;
    panel->formationType = formationType;
    if (func_ov001_0207a8fc(panel) != 0) {
        ApplyFormationSlots_020b6d90(formationType);
    }
}
