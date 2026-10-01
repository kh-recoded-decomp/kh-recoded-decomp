#include "nitro/types.h"

extern u32 func_02006770();
extern u32 func_ov091_020c173c();

void RequestEntryTransitionIfIdle_020c1764(u32 context)

{
  int result;
  
  result = func_02006770(0x400006c);
  if (result != 0) {
    return;
  }
  func_ov091_020c173c(2,context);
  return;
}
