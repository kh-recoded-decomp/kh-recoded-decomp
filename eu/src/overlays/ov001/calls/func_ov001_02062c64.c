#include "nitro/types.h"

typedef unsigned int code();

extern unsigned int data_ov001_020a0480;
extern unsigned int IsEntryFlag2Active();

unsigned int func_ov001_02062c64(void) {
  int result;

  if ((*(code **)(data_ov001_020a0480 + 0x2828) != (code *)0x0) &&
     (result = (**(code **)(data_ov001_020a0480 + 0x2828))(), result == 0)) {
    return 0;
  }
  result = IsEntryFlag2Active(0);
  if (result != 0) {
    return 0;
  }
  return 1;
}
