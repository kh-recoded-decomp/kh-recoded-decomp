#include "nitro/types.h"

extern unsigned int *gFieldEntryPoolManager;

void RegisterFieldEntryPool(int index,int entry) {
  *(int *)(*gFieldEntryPoolManager + index * 4) = entry;
  *(char *)(entry + 0x59) = (char)index;
}
