#include "nitro/types.h"

extern int *data_ov010_020a1de0;

int func_ov010_020a1978(void) {
  if (data_ov010_020a1de0 == (int *)0x0) {
    return 0;
  }
  if (*data_ov010_020a1de0 != 0) {
    return 1;
  }
  return 0;
}
