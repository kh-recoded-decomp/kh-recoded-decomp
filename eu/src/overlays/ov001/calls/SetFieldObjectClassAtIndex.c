#include "nitro/types.h"

extern unsigned int *data_ov001_020a04f8;

void SetFieldObjectClassAtIndex(int index,unsigned int entry) {
  *(unsigned int *)(*data_ov001_020a04f8 + index * 4) = entry;
}
