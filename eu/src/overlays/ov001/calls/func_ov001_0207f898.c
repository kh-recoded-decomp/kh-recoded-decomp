#include "nitro/types.h"

typedef unsigned int code();

unsigned int func_ov001_0207f898(int entry) {
  unsigned int result;
  code *callback;

  callback = *(code **)(*(int *)(entry + 8) + 0x34);
  if (callback != (code *)0x0) {
    result = (*callback)(entry);
    return result;
  }
  return 0;
}
