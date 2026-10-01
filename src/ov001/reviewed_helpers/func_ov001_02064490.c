#include "nitro/types.h"

typedef unsigned int code();

extern unsigned int data_ov001_020a0460;

unsigned int func_ov001_02064490(void) {
  unsigned int result;

  if (*(code **)(data_ov001_020a0460 + 0x2834) != (code *)0x0) {
    result = (**(code **)(data_ov001_020a0460 + 0x2834))();
    return result;
  }
  return 1;
}
