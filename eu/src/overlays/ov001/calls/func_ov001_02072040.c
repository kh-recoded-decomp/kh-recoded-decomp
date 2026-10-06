#include "nitro/types.h"

typedef unsigned int code();

typedef struct { unsigned char padding[4]; int value; } SharedState;
extern SharedState data_ov001_020a04c4;

unsigned int func_ov001_02072040(void) {
  int result;

  if ((*(code **)(data_ov001_020a04c4.value + 0x134c) != (code *)0x0) &&
     (result = (**(code **)(data_ov001_020a04c4.value + 0x134c))(), result != 0)) {
    return 1;
  }
  return 0;
}
