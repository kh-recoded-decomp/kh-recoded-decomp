#include "nitro/types.h"

extern unsigned int *data_ov001_020a04dc;

unsigned int func_ov001_02087214(int index) {
  return *(unsigned int *)(*data_ov001_020a04dc + index * 4);
}
