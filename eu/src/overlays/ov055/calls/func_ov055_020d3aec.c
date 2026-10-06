#include "nitro/types.h"

extern unsigned int NNSi_FndFreeFromDefaultHeap();
extern unsigned int ReleaseSceneObject();
extern unsigned int func_ov021_020af21c();

void func_ov055_020d3aec(int work) {
  if (*(char *)(*(int *)(work + 0x50) + 0x3d) == '\x04') {
    func_ov021_020af21c(*(int *)(work + 0x50));
  }
  ReleaseSceneObject(*(unsigned int *)(work + 0x50));
  NNSi_FndFreeFromDefaultHeap(*(unsigned int *)(work + 0x50));
}
