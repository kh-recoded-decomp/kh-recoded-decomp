#include "nitro/types.h"

typedef unsigned int code();

extern unsigned int IsObjectFlagClear();

unsigned int func_ov001_0207f84c(int entry,unsigned int firstValue,unsigned int secondValue) {
  int active;
  unsigned int result;
  code *callback;

  active = IsObjectFlagClear();
  if ((active != 0) && (callback = *(code **)(*(int *)(entry + 8) + 0x30), callback != (code *)0x0)) {
    result = (*callback)(entry,firstValue,secondValue);
    return result;
  }
  return 0;
}
