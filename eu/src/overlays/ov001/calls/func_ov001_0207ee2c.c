#include "nitro/types.h"

extern unsigned int *data_ov001_020a04f8;

void func_ov001_0207ee2c(int index,unsigned int entry) {
  *(unsigned int *)(*data_ov001_020a04f8 + index * 4) = entry;
}
