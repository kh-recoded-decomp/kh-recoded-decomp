#include "nitro/types.h"

extern void func_ov015_02072ee4(int state);
extern int func_ov015_020748e4(void);

void func_ov015_02072f7c(void) {
    int state;

    state = func_ov015_020748e4();
    if (state == 3) {
        return;
    }
    func_ov015_02072ee4(3);
}
