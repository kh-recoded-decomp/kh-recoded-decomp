#include "nitro/types.h"

extern unsigned int *gFieldOffsetTableHolder;
extern unsigned int NNSi_FndFreeFromDefaultHeap();

void ReleaseOffsetTableFile(void) {
  unsigned int *block;

  block = gFieldOffsetTableHolder;
  if (gFieldOffsetTableHolder != (unsigned int *)0x0) {
    if ((void *)*gFieldOffsetTableHolder != (void *)0x0) {
      NNSi_FndFreeFromDefaultHeap((void *)*gFieldOffsetTableHolder);
    }
    NNSi_FndFreeFromDefaultHeap(block);
    gFieldOffsetTableHolder = (unsigned int *)0x0;
  }
}
