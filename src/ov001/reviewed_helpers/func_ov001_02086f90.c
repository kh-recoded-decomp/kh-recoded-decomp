#include "nitro/types.h"

extern unsigned int *data_ov001_020a04dc;

void func_ov001_02086f90(int index,int entry) {
  *(int *)(*data_ov001_020a04dc + index * 4) = entry;
  *(char *)(entry + 0x59) = (char)index;
}
