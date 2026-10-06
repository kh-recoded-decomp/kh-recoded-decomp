#include "nitro/types.h"

extern unsigned int data_ov035_020bc500;
extern unsigned int PXI_Init_0202a64c();
extern unsigned int PopVramState();
extern unsigned int ReleaseMovieResources();
extern unsigned int ReleaseSeqArcHeapLevel();
extern unsigned int SuspendTaskAndSetFlag();
extern unsigned int func_ov035_020bac90();
extern unsigned int StoreToGlobalPtr4Field28();
extern unsigned int ActorRegistry_ClearCollisionResult();
extern unsigned int func_ov001_020676c4();
extern unsigned int func_ov001_020685d4();
extern unsigned int func_ov001_0207ef68();
extern unsigned int func_ov001_0207efa0();
extern unsigned int FreeMovieCharacterBuffers();
extern unsigned int FreeMovieSlotBuffers();
extern unsigned int func_ov035_020bb7a8();

unsigned int func_ov035_020ba6e4(void) {
  func_ov035_020bac90();
  FreeMovieSlotBuffers();
  FreeMovieCharacterBuffers();
  ReleaseMovieResources();
  *(u16 *)(data_ov035_020bc500 + 6) = *(u16 *)(data_ov035_020bc500 + 6) & 0xfff3;
  func_ov001_020685d4();
  func_ov001_020676c4();
  func_ov001_0207ef68(1);
  func_ov001_0207efa0();
  func_ov035_020bb7a8();
  if (*(int *)(data_ov035_020bc500 + 0x14) != -1) {
    PXI_Init_0202a64c(*(int *)(data_ov035_020bc500 + 0x14));
    *(unsigned int *)(data_ov035_020bc500 + 0x14) = 0xffffffff;
  }
  SuspendTaskAndSetFlag();
  PopVramState();
  ActorRegistry_ClearCollisionResult();
  ReleaseSeqArcHeapLevel(1);
  StoreToGlobalPtr4Field28(1);
  *(u16 *)(data_ov035_020bc500 + 6) = *(u16 *)(data_ov035_020bc500 + 6) | 0x8000;
  return 9;
}
