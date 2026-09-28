#include "nitro/types.h"

extern u32 data_ov035_020bc4e0;
extern int func_ov001_02086d00(void);
extern void func_ov001_020677fc(void);
extern void func_ov001_020687b8(void);
extern void InvokeListNodeCallbacks_0207eff0(void);
extern void func_ov035_020bacc4(int arg);

u32 func_ov035_020ba5f0(void) {
    if (func_ov001_02086d00() == 0) {
        return 0xffffffff;
    }
    func_ov001_020677fc();
    func_ov001_020687b8();
    InvokeListNodeCallbacks_0207eff0();
    func_ov035_020bacc4(1);
    *(u16 *)(data_ov035_020bc4e0 + 6) = *(u16 *)(data_ov035_020bc4e0 + 6) | 0x8000;
    return 4;
}
