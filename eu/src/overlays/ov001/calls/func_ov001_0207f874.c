#include "nitro/types.h"

typedef unsigned int code();

extern unsigned int IsObjectFlagClear();

unsigned int func_ov001_0207f874(int entry,unsigned int value) {
  int active;
  unsigned int result;
  code *callback;

  active = IsObjectFlagClear();
  if ((active != 0) && (callback = *(code **)(*(int *)(entry + 8) + 0x2c), callback != (code *)0x0)) {
    result = (*callback)(entry,value);
    return result;
  }
  return 0;
}
