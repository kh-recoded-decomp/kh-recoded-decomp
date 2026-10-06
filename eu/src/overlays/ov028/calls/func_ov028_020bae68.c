#include "nitro/types.h"

extern void func_02035de4(void);
extern void DrawVisibleSceneSlots(void);
extern void RunFlaggedEventCallbacks(void);
extern void func_ov001_020876d4(void);
extern void func_ov021_020af528(s32 value);

void func_ov028_020bae68(void)
{
    func_ov021_020af528(1);
    DrawVisibleSceneSlots();
    RunFlaggedEventCallbacks();
    func_02035de4();
    func_ov001_020876d4();
}
