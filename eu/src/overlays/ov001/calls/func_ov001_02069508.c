#include "nitro/types.h"

extern unsigned int *data_ov001_020a049c;
extern unsigned int NNSi_FndFreeFromDefaultHeap();

void func_ov001_02069508(void) {
  unsigned int *block;

  block = data_ov001_020a049c;
  if (data_ov001_020a049c != (unsigned int *)0x0) {
    if ((void *)*data_ov001_020a049c != (void *)0x0) {
      NNSi_FndFreeFromDefaultHeap((void *)*data_ov001_020a049c);
    }
    NNSi_FndFreeFromDefaultHeap(block);
    data_ov001_020a049c = (unsigned int *)0x0;
  }
}
