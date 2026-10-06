#include "nitro/types.h"

extern void func_ov021_020af528(s32 flag);
extern void DrawVisibleSceneSlots(void);
extern void RunFlaggedEventCallbacks(void);
extern void func_02035de4(void);
extern void func_ov001_020876d4(void);

void func_ov032_020bb36c(void) {
    func_ov021_020af528(1);
    DrawVisibleSceneSlots();
    RunFlaggedEventCallbacks();
    func_02035de4();
    func_ov001_020876d4();
}
