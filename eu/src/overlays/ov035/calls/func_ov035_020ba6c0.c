#include "nitro/types.h"

extern void func_ov035_020bad84(void);
extern int UpdateStageFrame(void);

u32 func_ov035_020ba6c0(void) {
    if (UpdateStageFrame() != 0) {
        func_ov035_020bad84();
        return 7;
    }
    return 0xffffffff;
}
