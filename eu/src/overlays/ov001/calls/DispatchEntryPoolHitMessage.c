#include "nitro/types.h"

typedef unsigned int code();

unsigned int DispatchEntryPoolHitMessage(int entry,unsigned int value) {
  unsigned int result;
  code *callback;

  callback = *(code **)(*(int *)(entry + 4) + 0x1c);
  if (callback != (code *)0x0) {
    result = (*callback)(entry,value);
    return result;
  }
  return 0;
}
