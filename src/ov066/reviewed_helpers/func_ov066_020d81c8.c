#include "nitro/types.h"

extern unsigned int NNSi_FndFreeFromDefaultHeap_0202a1c4();
extern unsigned int func_0202cd78();
extern unsigned int func_020c2f90();
extern unsigned int func_ov021_020ade38();

void func_ov066_020d81c8(int work,unsigned int value) {
  func_0202cd78(*(unsigned int *)(work + 0x84));
  func_ov021_020ade38(work,value);
  func_020c2f90(*(unsigned int *)(work + 0x88));
  NNSi_FndFreeFromDefaultHeap_0202a1c4(*(void **)(work + 0x88));
}
