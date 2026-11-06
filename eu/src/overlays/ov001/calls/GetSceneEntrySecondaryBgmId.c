#include "nitro/types.h"

extern unsigned int *gFieldSceneEntryContext;

u8 GetSceneEntrySecondaryBgmId(int index) {
  int entry;

  entry = *(int *)(*gFieldSceneEntryContext + index * 4 + 8);
  if (entry == 0) {
    return 0xff;
  }
  return *(u8 *)(entry + 0x19);
}
