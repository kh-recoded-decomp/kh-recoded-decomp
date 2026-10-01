#include "nitro/types.h"

extern unsigned int NNSi_FndFreeFromDefaultHeap_0202a1c4();
extern unsigned int func_0202cd78();
extern unsigned int func_020c2f90();

void func_ov064_020d86d0(int work) {
  func_0202cd78(*(unsigned int *)(work + 0x68));
  func_020c2f90(*(unsigned int *)(work + 0x6c));
  NNSi_FndFreeFromDefaultHeap_0202a1c4(*(void **)(work + 0x6c));
}
