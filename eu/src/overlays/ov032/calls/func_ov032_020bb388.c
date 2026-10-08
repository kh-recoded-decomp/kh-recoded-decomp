#include "nitro/types.h"

extern void ActorRegistry_ForEachCallback(s32 channelMask);
extern void UpdatePrizeOrbs(void);
extern void UpdateSceneAnimsAndCaption(s32 channelMask);
extern void UpdatePartyEntries(s32 channelMask);
extern void UpdateFieldObjectStates(s32 channelMask);
extern void StageManager_Update(s32 channelMask);

void func_ov032_020bb388(s32 keepAlive) {
    if (keepAlive == 0) {
        UpdateSceneAnimsAndCaption(0x1000);
        UpdateFieldObjectStates(0x1000);
    }
    UpdatePartyEntries(0x1000);
    if (keepAlive == 0) {
        StageManager_Update(0x1000);
        UpdatePrizeOrbs();
    }
    ActorRegistry_ForEachCallback(0x1000);
}
