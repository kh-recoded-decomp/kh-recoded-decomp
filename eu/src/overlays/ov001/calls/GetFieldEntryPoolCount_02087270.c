#include "nitro/types.h"

extern u32 gFieldEntryPoolManager;

int GetFieldEntryPoolCount_02087270(void) {
  return (int)*(char *)(gFieldEntryPoolManager + 4);
}
