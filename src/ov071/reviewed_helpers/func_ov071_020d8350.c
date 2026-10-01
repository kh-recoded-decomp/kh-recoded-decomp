#include "nitro/types.h"

extern unsigned int NNSi_FndFreeFromDefaultHeap_0202a1c4();
extern unsigned int func_0202cd78();
extern unsigned int func_020c2f90();

void func_ov071_020d8350(int work) {
  func_020c2f90(*(unsigned int *)(work + 0x48));
  NNSi_FndFreeFromDefaultHeap_0202a1c4(*(void **)(work + 0x48));
  func_0202cd78(*(unsigned int *)(work + 0x4c));
}
