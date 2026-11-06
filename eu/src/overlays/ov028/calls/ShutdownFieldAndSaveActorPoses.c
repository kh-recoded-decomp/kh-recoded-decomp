#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct {
    u8 pad_00[0x06];
    u16 flags;
} FieldContext;

extern FieldContext *gOv028FieldSceneWorkStorage;
extern BOOL Panel_TryBeginTransition4(void);
extern void SuspendTaskAndSetFlag(void);
extern void SetMenuHighlight(s32 enable);
extern s32 GetManagedActorCount(void);
extern void ReleaseActorSlotByIndex(s32 index);
extern VecFx32 *GetManagedActorPosition(s32 index);
extern u16 GetBiasAdjustedField(s32 index);
extern void StoreSessionSpawnPoint(s32 index, VecFx32 *position, u16 angle);
extern void ResetStageEventContext(void);
extern void SetOverlayLayerVisible(s32 value);
extern void ResetFieldObjectManagerResources(void);
extern void ShutdownSceneContext(void);
extern void ReleaseCounterHudModels(void);
extern void SnapshotManagedActorStateBlocks(void);
extern void PopVramState(void);
extern void ActorRegistry_ClearCollisionResult(void);
extern void ReleaseSeqArcHeapLevel(int index);
extern void StoreToGlobalPtr4Field28(int value);

s32 ShutdownFieldAndSaveActorPoses(void)
{
    s32 index;
    VecFx32 *position;

    if ((gOv028FieldSceneWorkStorage->flags & 0x10) == 0 && !Panel_TryBeginTransition4()) {
        return -1;
    }
    SuspendTaskAndSetFlag();
    SetMenuHighlight(1);
    for (index = 0; index < GetManagedActorCount(); index++) {
        ReleaseActorSlotByIndex(index);
        position = GetManagedActorPosition(index);
        StoreSessionSpawnPoint(index, position, GetBiasAdjustedField(index));
    }
    ResetStageEventContext();
    SetOverlayLayerVisible(1);
    ResetFieldObjectManagerResources();
    ShutdownSceneContext();
    gOv028FieldSceneWorkStorage->flags &= ~0xC;
    ReleaseCounterHudModels();
    SnapshotManagedActorStateBlocks();
    PopVramState();
    ActorRegistry_ClearCollisionResult();
    ReleaseSeqArcHeapLevel(1);
    StoreToGlobalPtr4Field28(1);
    gOv028FieldSceneWorkStorage->flags |= 0x8000;
    return 0x12;
}
