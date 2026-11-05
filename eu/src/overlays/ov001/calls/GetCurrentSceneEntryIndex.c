#include "nitro/types.h"

extern u32 data_ov001_020a048c;

int GetCurrentSceneEntryIndex(void) {
  return (int)*(char *)(data_ov001_020a048c + 0xd);
}
