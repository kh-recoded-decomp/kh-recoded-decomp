#include "nitro/types.h"

extern int *data_020613cc;
extern int NNSi_FndFreeFromDefaultHeap_0202a1c4();

void func_02050a44(void) {
  int *block;
  int references;

  block = data_020613cc;
  if ((data_020613cc != (int *)0x0) &&
     (references = *data_020613cc, *data_020613cc = references + -1, references + -1 == 0)) {
    if ((void *)block[0x27] != (void *)0x0) {
      NNSi_FndFreeFromDefaultHeap_0202a1c4((void *)block[0x27]);
      block[0x27] = 0;
    }
    NNSi_FndFreeFromDefaultHeap_0202a1c4(block);
    data_020613cc = (int *)0x0;
  }
}
