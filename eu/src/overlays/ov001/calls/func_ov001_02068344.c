#include "nitro/types.h"

extern unsigned int *data_ov001_020a048c;

int func_ov001_02068344(int groupIndex,int entryIndex) {
  return (int)*(char *)(*(int *)(*(int *)(*data_ov001_020a048c + groupIndex * 4 + 8) + 0x20) +
                       entryIndex * 8);
}
