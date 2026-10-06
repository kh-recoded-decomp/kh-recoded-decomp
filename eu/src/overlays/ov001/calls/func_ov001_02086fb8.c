#include "nitro/types.h"

extern unsigned int *data_ov001_020a04fc;

void func_ov001_02086fb8(int index,int entry) {
  *(int *)(*data_ov001_020a04fc + index * 4) = entry;
  *(char *)(entry + 0x59) = (char)index;
}
