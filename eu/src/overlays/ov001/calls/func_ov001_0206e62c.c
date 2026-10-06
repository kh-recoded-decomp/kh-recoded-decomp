#include "nitro/types.h"

extern unsigned int *data_ov001_020a04bc;

unsigned int func_ov001_0206e62c(void) {
  if (data_ov001_020a04bc == (unsigned int *)0x0) {
    return 0xffffffff;
  }
  return *data_ov001_020a04bc;
}
