#include "nitro/types.h"

extern u32 gTextWindowResourceTable;
extern u32 NNSi_FndFreeFromDefaultHeap();
extern u32 ZeroHalfThenFree();

void ReleaseTextWindowBackground(void) {
  if (*(void **)(gTextWindowResourceTable + 8) != (void *)0x0) {
    NNSi_FndFreeFromDefaultHeap(*(void **)(gTextWindowResourceTable + 8));
    *(u32 *)(gTextWindowResourceTable + 8) = 0;
  }
  ZeroHalfThenFree(*(u32 *)(gTextWindowResourceTable + 4));
}
