#include "nitro/types.h"

extern void func_ov021_020a75a4(int obj, int variant, int selectionIndex);
extern void RefreshActorState_020cce08(void);
extern void DestroyActorResources_020ccc60(void);
extern void DrawActor_020ccd24(void);
extern void UpdateActorAnimation_020cea48(void);
extern void RequestActorMode_020cde20(void);
extern void SetAnimationFrameAll_020cdfc0(void);
extern void ApplyIncomingHit_020ce2e8(void);
extern void PlayActorContextSound_020ce188(void);
extern void BuildActorStatusFlags_020ce5d4(void);
extern void SetEntityModeEnabled_020ce7a0(void);
extern void func_ov052_020ccf80(void);
extern void SetLinkedAngleIfUnlocked_020ceb94(void);
extern void SetModelsAlpha_020cc0d8(void);
extern void BuildSlot3HitSphere_020cbff8(void);
extern void func_ov052_020ccf9c(void);
extern void QueryTargetPosition_020cc068(void);
extern void SetSlotDisplayMode_020ca7d0(void);
extern void GetStateUnlessBlocked_020ca8d4(void);
extern void func_ov052_020cd338(void);
extern void DispatchSlotAction_020ced20(void);

void InstallActorCallbacks_020cce6c(int obj)
{
    func_ov021_020a75a4(obj, 0, *(u8 *)(obj + 0x9b4));
    *(void **)(obj + 0x1e4) = RefreshActorState_020cce08;
    *(void **)(obj + 0x1e0) = DestroyActorResources_020ccc60;
    *(void **)(obj + 0x1e8) = DrawActor_020ccd24;
    *(void **)(obj + 0x1ec) = UpdateActorAnimation_020cea48;
    *(void **)(obj + 0x1f8) = RequestActorMode_020cde20;
    *(void **)(obj + 0x1fc) = SetAnimationFrameAll_020cdfc0;
    *(void **)(obj + 0x208) = ApplyIncomingHit_020ce2e8;
    *(void **)(obj + 0x1f0) = PlayActorContextSound_020ce188;
    *(void **)(obj + 0x21c) = BuildActorStatusFlags_020ce5d4;
    *(void **)(obj + 0x20c) = SetEntityModeEnabled_020ce7a0;
    *(void **)(obj + 0x214) = func_ov052_020ccf80;
    *(void **)(obj + 0x210) = SetLinkedAngleIfUnlocked_020ceb94;
    *(void **)(obj + 0x204) = SetModelsAlpha_020cc0d8;
    *(void **)(obj + 0x220) = BuildSlot3HitSphere_020cbff8;
    *(void **)(obj + 0x224) = func_ov052_020ccf9c;
    *(void **)(obj + 0x228) = QueryTargetPosition_020cc068;
    *(void **)(obj + 0x200) = SetSlotDisplayMode_020ca7d0;
    *(void **)(obj + 0x22c) = GetStateUnlessBlocked_020ca8d4;
    *(void **)(obj + 0x10ec) = func_ov052_020cd338;
    *(int *)(obj + 0x10e8) = 0;
    *(int *)(obj + 0x10f0) = 0;
    *(int *)(obj + 0x10f4) = 0;
    *(int *)(obj + 0x10f8) = 0;
    *(void **)(obj + 0x10fc) = DispatchSlotAction_020ced20;
}
