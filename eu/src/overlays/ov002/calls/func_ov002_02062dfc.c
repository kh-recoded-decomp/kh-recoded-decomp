#include "nitro/types.h"

extern s32 UpdatePanelState_0206cf38(void);
extern void SwitchPanelMode(s32 value);

void func_ov002_02062dfc(void) {
    s32 status = UpdatePanelState_0206cf38();
    if (status != 1) {
        return;
    }
    SwitchPanelMode(0);
}
