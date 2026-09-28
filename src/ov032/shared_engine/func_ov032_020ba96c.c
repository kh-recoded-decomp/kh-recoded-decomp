#include "nitro/types.h"

extern s32 func_ov001_02086d00(void);
extern void func_ov001_02067704(void);

s32 func_ov032_020ba96c(void) {
    s32 ready = func_ov001_02086d00();
    if (ready == 0) {
        return -1;
    }
    func_ov001_02067704();
    return 4;
}
