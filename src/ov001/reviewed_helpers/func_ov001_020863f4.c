#include "nitro/types.h"

typedef unsigned int code();

unsigned int func_ov001_020863f4(int entry) {
  unsigned int result;
  code *callback;

  if ((*(u16 *)(entry + 0x30) & 8) == 0) {
    return 0;
  }
  callback = *(code **)(*(int *)(entry + 4) + 0x28);
  if (callback != (code *)0x0) {
    result = (*callback)(entry);
    return result;
  }
  return 0;
}
