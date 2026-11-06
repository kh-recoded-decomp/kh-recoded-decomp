#include "nitro/types.h"

extern u32 gFieldObjectClassManager;

int GetFieldObjectClassCount(void) {
  return (int)*(char *)(gFieldObjectClassManager + 4);
}
