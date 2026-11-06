#include "nitro/types.h"

extern unsigned int *gFieldObjectClassManager;

unsigned int GetFieldObjectClassAtIndex(int index) {
  return *(unsigned int *)(*gFieldObjectClassManager + index * 4);
}
