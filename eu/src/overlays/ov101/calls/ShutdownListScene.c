#include "src/overlays/ov101/ListSceneState.h"

extern const u8 sOv101_VblankFunc_020c1f78[];
extern ListSceneState *data_ov101_020c5920;
extern void NotifyBothOrOne(u32 channel, u32 registration, int index);
extern void ShutdownPageInteractionState(ListSceneState *scene);
extern void ReleaseStateBuffers(ListSceneState *scene);
extern void ReleaseStateSlotLists(ListSceneState *scene);
extern void ShutdownStateHandlers(ListSceneState *scene);
extern void FreeMenuResourceSlots(ListSceneState *scene);
extern void FreeStateBuffers(ListSceneState *scene);
extern void SetStateFlagBits(int setIndex, int flags);

void ShutdownListScene(ListSceneState *scene)
{
    NotifyBothOrOne(1, (u32)sOv101_VblankFunc_020c1f78, 0);
    ShutdownPageInteractionState(scene);
    ReleaseStateBuffers(scene);
    ReleaseStateSlotLists(scene);
    ShutdownStateHandlers(scene);
    FreeMenuResourceSlots(scene);
    FreeStateBuffers(scene);
    SetStateFlagBits(0, 5);
    data_ov101_020c5920 = NULL;
}
