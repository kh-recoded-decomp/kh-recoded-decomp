#include "nitro/types.h"

extern u32 data_ov028_020bb3a0;
extern void ActorRegistry_ForEachCallback(u32 size);
extern void UpdatePrizeOrbs(void);
extern void UpdateSceneAnimsAndCaption(u32 size);
extern void UpdatePartyEntries(u32 size);
extern void UpdateFieldObjectStates(u32 size);
extern void StageManager_Update(u32 size);

void func_ov028_020bae88(s32 mode)
{
    u32 budget = 0x1000;

    if ((*(u16 *)(data_ov028_020bb3a0 + 6) & 0x40) != 0) {
        budget = 0x100;
    }
    if (mode == 0) {
        UpdateSceneAnimsAndCaption(0x1000);
        UpdateFieldObjectStates(0x1000);
    }
    UpdatePartyEntries(budget);
    if (mode == 0) {
        StageManager_Update(budget);
        UpdatePrizeOrbs();
    }
    ActorRegistry_ForEachCallback(0x1000);
}
