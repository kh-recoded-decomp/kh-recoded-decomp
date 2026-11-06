#include "nitro/types.h"

extern u32 gFieldEntryPoolManager;

int GetFieldEntryPoolCount(void) {
  return (int)*(char *)(gFieldEntryPoolManager + 4);
}
