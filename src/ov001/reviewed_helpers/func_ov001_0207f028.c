#include "nitro/types.h"

extern unsigned int *data_ov001_020a04d8;

unsigned int func_ov001_0207f028(int index) {
  return *(unsigned int *)(*data_ov001_020a04d8 + index * 4);
}
