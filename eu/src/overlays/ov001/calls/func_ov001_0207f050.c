#include "nitro/types.h"

extern unsigned int *data_ov001_020a04f8;

unsigned int func_ov001_0207f050(int index) {
  return *(unsigned int *)(*data_ov001_020a04f8 + index * 4);
}
