#define func_ov001_0206de40 ReleaseActorSlotByIndex
#include "nitro/types.h"

typedef struct { unsigned char padding[4]; int value; } SharedState;
extern SharedState data_ov032_020c0080;
extern unsigned int StoreToGlobalPtr4Field28();
extern unsigned int ActorRegistry_ClearCollisionResult();
extern unsigned int PopVramState();
extern unsigned int ReleaseSeqArcHeapLevel();
extern unsigned int StoreSessionSpawnPoint();
extern unsigned int SnapshotManagedActorStateBlocks();
extern unsigned int SuspendTaskAndSetFlag();
extern unsigned int ShutdownSceneContext();
extern unsigned int ResetStageEventContext();
extern unsigned int SetMenuHighlight();
extern unsigned int GetManagedActorCount();
extern unsigned int GetManagedActorPosition();
extern unsigned int GetBiasAdjustedField();
extern unsigned int func_ov001_0206de40();
extern unsigned int Panel_TryBeginTransition4();
extern unsigned int ReleaseCounterHudModels();
extern unsigned int SetOverlayLayerVisible();
extern unsigned int ResetFieldObjectManagerResources();

unsigned int GroupSceneState_SaveActorPosesAndExit(void) {
  int countOrGate;
  unsigned int firstValue;
  unsigned int secondValue;
  int index;

  if (((*(u16 *)(data_ov032_020c0080.value + 6) & 0x10) == 0) &&
     (countOrGate = Panel_TryBeginTransition4(), countOrGate == 0)) {
    return 0xffffffff;
  }
  SuspendTaskAndSetFlag();
  SetMenuHighlight(1);
  index = 0;
  countOrGate = GetManagedActorCount();
  if (0 < countOrGate) {
    do {
      func_ov001_0206de40(index);
      firstValue = GetManagedActorPosition(index);
      secondValue = GetBiasAdjustedField(index);
      StoreSessionSpawnPoint(index,firstValue,secondValue);
      index = index + 1;
      countOrGate = GetManagedActorCount();
    } while (index < countOrGate);
  }
  ResetStageEventContext();
  ShutdownSceneContext();
  SetOverlayLayerVisible(1);
  ResetFieldObjectManagerResources();
  *(u16 *)(data_ov032_020c0080.value + 6) = *(u16 *)(data_ov032_020c0080.value + 6) & 0xfff3;
  ReleaseCounterHudModels();
  SnapshotManagedActorStateBlocks();
  PopVramState();
  ActorRegistry_ClearCollisionResult();
  ReleaseSeqArcHeapLevel(1);
  StoreToGlobalPtr4Field28(1);
  *(u16 *)(data_ov032_020c0080.value + 6) = *(u16 *)(data_ov032_020c0080.value + 6) | 0x8000;
  return 0x11;
}
