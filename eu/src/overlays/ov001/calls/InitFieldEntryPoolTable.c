#include "nitro/types.h"

extern unsigned int gFieldSessionWork;
extern unsigned int gFieldEntryPoolManager;
extern unsigned int NNSi_FndAllocFromDefaultHeap();
extern unsigned int ResourceCache_FreeAll();
extern unsigned int MIi_CpuClear32();
extern unsigned int GetCurrentFieldEntryKey();
extern unsigned int IsSessionFlagSet();

void InitFieldEntryPoolTable(int count) {
  unsigned int *cache;
  void *entries;
  int currentState;

  cache = gFieldEntryPoolManager;
  entries = NNSi_FndAllocFromDefaultHeap(count * 4);
  *cache = entries;
  MIi_CpuClear32(0,entries,count * 4);
  *(char *)(cache + 1) = (char)count;
  currentState = IsSessionFlagSet(0x3614);
  if ((currentState == 0) &&
     (((currentState = GetCurrentFieldEntryKey(), *(short *)((int)cache + 0x132) != currentState ||
       (*(char *)(cache + 0x4d) != count)) ||
      ((*(u32 *)(gFieldSessionWork + 0x214) << 0x1b >> 0x1f) != 0)))) {
    ResourceCache_FreeAll();
  }
}
