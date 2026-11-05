#include "nitro/types.h"

extern s32 UpdatePanelState_0206cf38(void);
extern void SwitchPanelMode(s32 value);

void UpdateOv002ChildPanel(void) {
    s32 status = UpdatePanelState_0206cf38();
    if (status != 1) {
        return;
    }
    SwitchPanelMode(0);
}
