#include "nitro/types.h"

extern unsigned int *gFieldObjectClassManager;

void SetFieldObjectClassAtIndex(int index,unsigned int entry) {
  *(unsigned int *)(*gFieldObjectClassManager + index * 4) = entry;
}
