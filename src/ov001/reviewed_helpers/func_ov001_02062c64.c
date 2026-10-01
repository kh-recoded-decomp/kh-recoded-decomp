#include "nitro/types.h"

typedef unsigned int code();

extern unsigned int data_ov001_020a0460;
extern unsigned int func_ov001_020642d0();

unsigned int func_ov001_02062c64(void) {
  int result;

  if ((*(code **)(data_ov001_020a0460 + 0x2828) != (code *)0x0) &&
     (result = (**(code **)(data_ov001_020a0460 + 0x2828))(), result == 0)) {
    return 0;
  }
  result = func_ov001_020642d0(0);
  if (result != 0) {
    return 0;
  }
  return 1;
}
