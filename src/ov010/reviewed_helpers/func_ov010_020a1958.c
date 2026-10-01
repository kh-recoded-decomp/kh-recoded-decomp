#include "nitro/types.h"

extern int *data_ov010_020a1dc0;

int func_ov010_020a1958(void) {
  if (data_ov010_020a1dc0 == (int *)0x0) {
    return 0;
  }
  if (*data_ov010_020a1dc0 != 0) {
    return 1;
  }
  return 0;
}
