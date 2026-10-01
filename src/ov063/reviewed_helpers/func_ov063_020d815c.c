#include "nitro/types.h"

extern unsigned int NNSi_FndFreeFromDefaultHeap_0202a1c4();
extern unsigned int func_0202cd78();
extern unsigned int func_020c2f90();
extern unsigned int func_ov021_020aafac();

void func_ov063_020d815c(int work) {
  func_0202cd78(*(unsigned int *)(work + 0x54));
  func_ov021_020aafac(*(unsigned int *)(work + 0x58));
  NNSi_FndFreeFromDefaultHeap_0202a1c4(*(void **)(work + 0x58));
  func_020c2f90(*(unsigned int *)(work + 0x5c));
  NNSi_FndFreeFromDefaultHeap_0202a1c4(*(void **)(work + 0x5c));
}
