#include "nitro/types.h"

extern unsigned int gMovieContextState;
extern unsigned int DestroyTaskObjectWrapper();
extern unsigned int PopVramState();
extern unsigned int ReleaseMovieResources();
extern unsigned int ReleaseSeqArcHeapLevel();
extern unsigned int SuspendTaskAndSetFlag();
extern unsigned int AreaSceneCleanupNoOp();
extern unsigned int StoreToGlobalPtr4Field28();
extern unsigned int ActorRegistry_ClearCollisionResult();
extern unsigned int ShutdownSceneContext();
extern unsigned int ResetStageEventContext();
extern unsigned int SetOverlayLayerVisible();
extern unsigned int ResetFieldObjectManagerResources();
extern unsigned int FreeMovieCharacterBuffers();
extern unsigned int FreeMovieSlotBuffers();
extern unsigned int FreeAreaMaterialFadeWork();

unsigned int AreaSceneState_ReleaseResourcesAndExit(void) {
  AreaSceneCleanupNoOp();
  FreeMovieSlotBuffers();
  FreeMovieCharacterBuffers();
  ReleaseMovieResources();
  *(u16 *)(gMovieContextState + 6) = *(u16 *)(gMovieContextState + 6) & 0xfff3;
  ResetStageEventContext();
  ShutdownSceneContext();
  SetOverlayLayerVisible(1);
  ResetFieldObjectManagerResources();
  FreeAreaMaterialFadeWork();
  if (*(int *)(gMovieContextState + 0x14) != -1) {
    DestroyTaskObjectWrapper(*(int *)(gMovieContextState + 0x14));
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
