#include "nitro/types.h"

typedef unsigned int code();

extern unsigned int func_ov001_0207f7a4();

unsigned int func_ov001_0207f84c(int entry,unsigned int value) {
  int active;
  unsigned int result;
  code *callback;

  active = func_ov001_0207f7a4();
  if ((active != 0) && (callback = *(code **)(*(int *)(entry + 8) + 0x2c), callback != (code *)0x0)) {
    result = (*callback)(entry,value);
    return result;
  }
  return 0;
}
