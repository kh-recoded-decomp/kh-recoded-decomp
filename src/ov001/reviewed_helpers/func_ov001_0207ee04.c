#include "nitro/types.h"

extern unsigned int *data_ov001_020a04d8;

void func_ov001_0207ee04(int index,unsigned int entry) {
  *(unsigned int *)(*data_ov001_020a04d8 + index * 4) = entry;
}
