#include "nitro/types.h"

typedef unsigned int code();

extern unsigned int gFieldSessionWork;
extern unsigned int IsEntryFlag2Active();

unsigned int IsSessionScriptEntryReady(void) {
  int result;

  if ((*(code **)(gFieldSessionWork + 0x2828) != (code *)0x0) &&
     (result = (**(code **)(gFieldSessionWork + 0x2828))(), result == 0)) {
    return 0;
  }
  result = IsEntryFlag2Active(0);
  if (result != 0) {
    return 0;
  }
  return 1;
}
