#include "nitro/types.h"

extern void UpdateActorSlotsAndBillboards(void);
extern void DrawVisibleSceneSlots(void);
extern void RunFlaggedEventCallbacks(void);
extern void func_ov001_020876d4(void);
extern void func_ov021_020af528(s32 value);

void func_ov028_020bae68(void)
{
    func_ov021_020af528(1);
    DrawVisibleSceneSlots();
    RunFlaggedEventCallbacks();
    UpdateActorSlotsAndBillboards();
    func_ov001_020876d4();
}
