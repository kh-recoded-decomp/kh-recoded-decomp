#include "nitro/types.h"

extern u32 gFieldSceneEntryContext;

int GetCurrentSceneEntryIndex(void) {
  return (int)*(char *)(gFieldSceneEntryContext + 0xd);
}
