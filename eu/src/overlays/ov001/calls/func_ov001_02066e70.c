#include "nitro/types.h"

extern signed char *data_ov001_020a0488;

unsigned int func_ov001_02066e70(void) {
  if ((*data_ov001_020a0488 != '\0') && (*data_ov001_020a0488 != '\x03')) {
    return 1;
  }
  return 0;
}
