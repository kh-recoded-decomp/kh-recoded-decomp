#include "nitro/types.h"

extern u32 data_ov035_020bc500;
extern int StepResourceSlotLoading(void);
extern void InvokeSceneCallback(void);
extern void func_ov001_020687b8(void);
extern void InvokeListNodeCallbacks(void);
extern void func_ov035_020bace4(int arg);

u32 func_ov035_020ba610(void) {
    if (StepResourceSlotLoading() == 0) {
        return 0xffffffff;
    }
    InvokeSceneCallback();
    func_ov001_020687b8();
    InvokeListNodeCallbacks();
    func_ov035_020bace4(1);
    *(u16 *)(data_ov035_020bc500 + 6) = *(u16 *)(data_ov035_020bc500 + 6) | 0x8000;
    return 4;
}
