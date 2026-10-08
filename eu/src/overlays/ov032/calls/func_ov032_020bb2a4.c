#define func_ov001_0206de40 ReleaseActorSlotByIndex
#include "nitro/types.h"

typedef struct { unsigned char padding[4]; int value; } SharedState;
extern SharedState data_ov032_020c0080;
extern unsigned int StoreToGlobalPtr4Field28();
extern unsigned int ActorRegistry_ClearCollisionResult();
extern unsigned int PopVramState();
extern unsigned int ReleaseSeqArcHeapLevel();
extern unsigned int StoreSessionSpawnPoint();
extern unsigned int func_ov001_02064d88();
extern unsigned int SuspendTaskAndSetFlag();
extern unsigned int ShutdownSceneContext();
extern unsigned int func_ov001_020685d4();
extern unsigned int SetMenuHighlight();
extern unsigned int func_ov001_0206dc38();
extern unsigned int func_ov001_0206dc4c();
extern unsigned int GetBiasAdjustedField();
extern unsigned int func_ov001_0206de40();
extern unsigned int Panel_TryBeginTransition4();
extern unsigned int func_ov001_0207d680();
extern unsigned int SetOverlayLayerVisible();
extern unsigned int func_ov001_0207efa0();

unsigned int func_ov032_020bb2a4(void) {
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
  countOrGate = func_ov001_0206dc38();
  if (0 < countOrGate) {
    do {
      func_ov001_0206de40(index);
      firstValue = func_ov001_0206dc4c(index);
      secondValue = GetBiasAdjustedField(index);
      StoreSessionSpawnPoint(index,firstValue,secondValue);
      index = index + 1;
      countOrGate = func_ov001_0206dc38();
    } while (index < countOrGate);
  }
  func_ov001_020685d4();
  ShutdownSceneContext();
  SetOverlayLayerVisible(1);
  func_ov001_0207efa0();
  *(u16 *)(data_ov032_020c0080.value + 6) = *(u16 *)(data_ov032_020c0080.value + 6) & 0xfff3;
  func_ov001_0207d680();
  func_ov001_02064d88();
  PopVramState();
  ActorRegistry_ClearCollisionResult();
  ReleaseSeqArcHeapLevel(1);
  StoreToGlobalPtr4Field28(1);
  *(u16 *)(data_ov032_020c0080.value + 6) = *(u16 *)(data_ov032_020c0080.value + 6) | 0x8000;
  return 0x11;
}
