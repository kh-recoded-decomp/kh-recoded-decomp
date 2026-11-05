#include "nitro/types.h"

extern unsigned int NNSi_FndFreeFromDefaultHeap();
extern unsigned int ReleaseSceneObject();
extern unsigned int FreeSlotTrackerUnitSlots();

void ReleaseSceneObjectAndFreeWork(int work) {
  if (*(char *)(*(int *)(work + 0x50) + 0x3d) == '\x04') {
    FreeSlotTrackerUnitSlots(*(int *)(work + 0x50));
  }
  ReleaseSceneObject(*(unsigned int *)(work + 0x50));
  NNSi_FndFreeFromDefaultHeap(*(unsigned int *)(work + 0x50));
}
