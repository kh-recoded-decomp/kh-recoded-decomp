#include "nitro/types.h"

extern unsigned int *data_ov001_020a04d8;
extern unsigned int NNSi_FndAllocFromDefaultHeap_0202a178();
extern unsigned int ResourceCache_LoadModeTables_02087348();
extern unsigned int func_01ff86fc();

void func_ov001_0207edd8(int count) {
  void *entries;

  entries = NNSi_FndAllocFromDefaultHeap_0202a178(count * 4);
  *data_ov001_020a04d8 = entries;
  func_01ff86fc(0,*data_ov001_020a04d8,count * 4);
  *(char *)(data_ov001_020a04d8 + 1) = (char)count;
  ResourceCache_LoadModeTables_02087348();
}
