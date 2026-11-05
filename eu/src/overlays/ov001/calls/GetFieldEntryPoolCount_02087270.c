#include "nitro/types.h"

extern u32 data_ov001_020a04fc;

int GetFieldEntryPoolCount_02087270(void) {
  return (int)*(char *)(data_ov001_020a04fc + 4);
}
