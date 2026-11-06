#include "nitro/types.h"

extern unsigned int *gManagedActorGlobals;

unsigned int GetManagedActorMode(void) {
  if (gManagedActorGlobals == (unsigned int *)0x0) {
    return 0xffffffff;
  }
  return *gManagedActorGlobals;
}
