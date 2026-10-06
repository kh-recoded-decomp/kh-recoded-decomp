#include "nitro/types.h"

extern unsigned int *data_ov001_020a04fc;

unsigned int func_ov001_0208723c(int index) {
  return *(unsigned int *)(*data_ov001_020a04fc + index * 4);
}
