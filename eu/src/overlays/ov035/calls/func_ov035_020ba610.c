#include "nitro/types.h"

extern u32 gMovieContextState;
extern int StepResourceSlotLoading(void);
extern void InvokeSceneCallback(void);
extern void func_ov001_020687b8(void);
extern void InvokeListNodeCallbacks(void);
extern void StartOverlay40Phase(int arg);

u32 func_ov035_020ba610(void) {
    if (StepResourceSlotLoading() == 0) {
        return 0xffffffff;
    }
    InvokeSceneCallback();
    func_ov001_020687b8();
    InvokeListNodeCallbacks();
    StartOverlay40Phase(1);
    *(u16 *)(gMovieContextState + 6) = *(u16 *)(gMovieContextState + 6) | 0x8000;
    return 4;
}
