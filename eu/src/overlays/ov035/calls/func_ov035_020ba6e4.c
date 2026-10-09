#include "nitro/types.h"

extern unsigned int gMovieContextState;
extern unsigned int PXI_Init_0202a64c();
extern unsigned int PopVramState();
extern unsigned int ReleaseMovieResources();
extern unsigned int ReleaseSeqArcHeapLevel();
extern unsigned int SuspendTaskAndSetFlag();
extern unsigned int func_ov035_020bac90();
extern unsigned int StoreToGlobalPtr4Field28();
extern unsigned int ActorRegistry_ClearCollisionResult();
extern unsigned int ShutdownSceneContext();
extern unsigned int func_ov001_020685d4();
extern unsigned int SetOverlayLayerVisible();
extern unsigned int func_ov001_0207efa0();
extern unsigned int FreeMovieCharacterBuffers();
extern unsigned int FreeMovieSlotBuffers();
extern unsigned int func_ov035_020bb7a8();

unsigned int func_ov035_020ba6e4(void) {
  func_ov035_020bac90();
  FreeMovieSlotBuffers();
  FreeMovieCharacterBuffers();
  ReleaseMovieResources();
  *(u16 *)(gMovieContextState + 6) = *(u16 *)(gMovieContextState + 6) & 0xfff3;
  func_ov001_020685d4();
  ShutdownSceneContext();
  SetOverlayLayerVisible(1);
  func_ov001_0207efa0();
  func_ov035_020bb7a8();
  if (*(int *)(gMovieContextState + 0x14) != -1) {
    PXI_Init_0202a64c(*(int *)(gMovieContextState + 0x14));
    *(unsigned int *)(gMovieContextState + 0x14) = 0xffffffff;
  }
  SuspendTaskAndSetFlag();
  PopVramState();
  ActorRegistry_ClearCollisionResult();
  ReleaseSeqArcHeapLevel(1);
  StoreToGlobalPtr4Field28(1);
  *(u16 *)(gMovieContextState + 6) = *(u16 *)(gMovieContextState + 6) | 0x8000;
  return 9;
}
