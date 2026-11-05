#include "nitro/types.h"

extern u32 data_ov001_020a04f8;

int GetFieldObjectClassCount(void) {
  return (int)*(char *)(data_ov001_020a04f8 + 4);
}
