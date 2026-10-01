#include "nitro/types.h"

extern unsigned int *data_ov002_0206c46c;
extern unsigned int NNSi_FndAllocFromDefaultHeap_0202a178();
extern unsigned int NNSi_FndFreeFromDefaultHeap_0202a1c4();
extern unsigned int func_01ff8830();

void func_ov002_020666c8(unsigned int value) {
  if (data_ov002_0206c46c != (void *)0x0) {
    NNSi_FndFreeFromDefaultHeap_0202a1c4(data_ov002_0206c46c);
    data_ov002_0206c46c = (void *)0x0;
  }
  data_ov002_0206c46c = NNSi_FndAllocFromDefaultHeap_0202a178(0x2c);
  func_01ff8830(data_ov002_0206c46c,0,0x2c);
  *data_ov002_0206c46c = value;
}
