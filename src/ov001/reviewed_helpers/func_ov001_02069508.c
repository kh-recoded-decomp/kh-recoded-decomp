#include "nitro/types.h"

extern unsigned int *data_ov001_020a047c;
extern unsigned int NNSi_FndFreeFromDefaultHeap_0202a1c4();

void func_ov001_02069508(void) {
  unsigned int *block;

  block = data_ov001_020a047c;
  if (data_ov001_020a047c != (unsigned int *)0x0) {
    if ((void *)*data_ov001_020a047c != (void *)0x0) {
      NNSi_FndFreeFromDefaultHeap_0202a1c4((void *)*data_ov001_020a047c);
    }
    NNSi_FndFreeFromDefaultHeap_0202a1c4(block);
    data_ov001_020a047c = (unsigned int *)0x0;
  }
}
