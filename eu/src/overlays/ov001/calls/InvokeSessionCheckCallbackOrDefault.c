#include "nitro/types.h"

typedef unsigned int code();

extern unsigned int gFieldSessionWork;

unsigned int InvokeSessionCheckCallbackOrDefault(void) {
  unsigned int result;

  if (*(code **)(gFieldSessionWork + 0x2834) != (code *)0x0) {
    result = (**(code **)(gFieldSessionWork + 0x2834))();
    return result;
  }
  return 1;
}
