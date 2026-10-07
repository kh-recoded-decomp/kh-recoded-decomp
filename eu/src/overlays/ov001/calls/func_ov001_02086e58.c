#include "nitro/types.h"

extern unsigned int data_ov001_020a0480;
extern unsigned int data_ov001_020a04fc;
extern unsigned int NNSi_FndAllocFromDefaultHeap();
extern unsigned int ResourceCache_FreeAll();
extern unsigned int MIi_CpuClear32();
extern unsigned int func_ov001_020644c0();
extern unsigned int IsSessionFlagSet();

void func_ov001_02086e58(int count) {
  unsigned int *cache;
  void *entries;
  int currentState;

  cache = data_ov001_020a04fc;
  entries = NNSi_FndAllocFromDefaultHeap(count * 4);
  *cache = entries;
  MIi_CpuClear32(0,entries,count * 4);
  *(char *)(cache + 1) = (char)count;
  currentState = IsSessionFlagSet(0x3614);
  if ((currentState == 0) &&
     (((currentState = func_ov001_020644c0(), *(short *)((int)cache + 0x132) != currentState ||
       (*(char *)(cache + 0x4d) != count)) ||
      ((*(u32 *)(data_ov001_020a0480 + 0x214) << 0x1b >> 0x1f) != 0)))) {
    ResourceCache_FreeAll();
  }
}
