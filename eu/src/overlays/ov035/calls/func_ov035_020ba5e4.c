#include "nitro/types.h"

extern u32 data_ov035_020bc500;
extern int AreAllListNodesReady(void);
extern void func_ov001_020871a0(void);

u32 func_ov035_020ba5e4(void) {
    if (AreAllListNodesReady() == 0) {
        return 0xffffffff;
    }
    func_ov001_020871a0();
    *(u16 *)(data_ov035_020bc500 + 6) = *(u16 *)(data_ov035_020bc500 + 6) | 0x8000;
    return 3;
}
