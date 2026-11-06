#include "nitro/types.h"

extern u32 gCameraSceneGlobalStorage;
extern u32 GetEntryFieldForMode();

void GetCameraAdjustedHorizontalBounds(int *outFirst,int *outSecond) {
  int *entry;
  int offset;

  *outFirst = *(int *)(gCameraSceneGlobalStorage + 0xc4) + *(int *)(gCameraSceneGlobalStorage + 0x54);
  *outSecond = *(int *)(gCameraSceneGlobalStorage + 200) + *(int *)(gCameraSceneGlobalStorage + 0x58);
  entry = (int *)GetEntryFieldForMode(0);
  offset = *(int *)(*(int *)(*entry + 0x130) + 0x28);
  *outFirst = *outFirst + offset;
  *outSecond = *outSecond - offset;
}
