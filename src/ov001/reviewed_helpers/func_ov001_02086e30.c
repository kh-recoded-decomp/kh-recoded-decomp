#include "nitro/types.h"

extern unsigned int data_ov001_020a0460;
extern unsigned int data_ov001_020a04dc;
extern unsigned int NNSi_FndAllocFromDefaultHeap_0202a178();
extern unsigned int ResourceCache_FreeAll_02086df0();
extern unsigned int func_01ff86fc();
extern unsigned int func_ov001_020644c0();
extern unsigned int func_ov001_020645c8();

void func_ov001_02086e30(int count) {
  unsigned int *cache;
  void *entries;
  int currentState;

  cache = data_ov001_020a04dc;
  entries = NNSi_FndAllocFromDefaultHeap_0202a178(count * 4);
  *cache = entries;
  func_01ff86fc(0,entries,count * 4);
  *(char *)(cache + 1) = (char)count;
  currentState = func_ov001_020645c8(0x3614);
  if ((currentState == 0) &&
     (((currentState = func_ov001_020644c0(), *(short *)((int)cache + 0x132) != currentState ||
       (*(char *)(cache + 0x4d) != count)) ||
      ((*(u32 *)(data_ov001_020a0460 + 0x214) << 0x1b >> 0x1f) != 0)))) {
    ResourceCache_FreeAll_02086df0();
  }
}
