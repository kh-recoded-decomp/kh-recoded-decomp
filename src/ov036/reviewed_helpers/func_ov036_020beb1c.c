#include "nitro/types.h"

extern u32 data_ov036_020c3844;
extern u32 NNSi_FndFreeFromDefaultHeap_0202a1c4();
extern u32 func_0202cd78();

void func_ov036_020beb1c(void) {
  if (*(void **)(data_ov036_020c3844 + 8) != (void *)0x0) {
    NNSi_FndFreeFromDefaultHeap_0202a1c4(*(void **)(data_ov036_020c3844 + 8));
    *(u32 *)(data_ov036_020c3844 + 8) = 0;
  }
  func_0202cd78(*(u32 *)(data_ov036_020c3844 + 4));
}
