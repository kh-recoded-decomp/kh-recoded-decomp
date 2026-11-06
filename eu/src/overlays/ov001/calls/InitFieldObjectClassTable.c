#include "nitro/types.h"

extern unsigned int *gFieldObjectClassManager;
extern unsigned int NNSi_FndAllocFromDefaultHeap();
extern unsigned int ResourceCache_LoadModeTables();
extern unsigned int MIi_CpuClear32();

void InitFieldObjectClassTable(int count) {
  void *entries;

  entries = NNSi_FndAllocFromDefaultHeap(count * 4);
  *gFieldObjectClassManager = entries;
  MIi_CpuClear32(0,*gFieldObjectClassManager,count * 4);
  *(char *)(gFieldObjectClassManager + 1) = (char)count;
  ResourceCache_LoadModeTables();
}
