#include "nitro/types.h"

extern void func_ov015_02072ee4(int state);
extern int GetPanelTransitionMode(void);

void func_ov015_02072f7c(void) {
    int state;

    state = GetPanelTransitionMode();
    if (state == 3) {
        return;
    }
    func_ov015_02072ee4(3);
}
