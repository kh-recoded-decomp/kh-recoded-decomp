#include "nitro/types.h"

extern unsigned int *gFieldEntryPoolManager;

unsigned int GetFieldEntryPoolAtIndex(int index) {
  return *(unsigned int *)(*gFieldEntryPoolManager + index * 4);
}
