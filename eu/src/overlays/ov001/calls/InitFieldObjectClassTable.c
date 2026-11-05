#include "nitro/types.h"

extern unsigned int *data_ov001_020a04f8;
extern unsigned int NNSi_FndAllocFromDefaultHeap();
extern unsigned int ResourceCache_LoadModeTables();
extern unsigned int MIi_CpuClear32();

void InitFieldObjectClassTable(int count) {
  void *entries;

  entries = NNSi_FndAllocFromDefaultHeap(count * 4);
  *data_ov001_020a04f8 = entries;
  MIi_CpuClear32(0,*data_ov001_020a04f8,count * 4);
  *(char *)(data_ov001_020a04f8 + 1) = (char)count;
  ResourceCache_LoadModeTables();
}
