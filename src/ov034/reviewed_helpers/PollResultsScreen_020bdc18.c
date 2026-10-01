#include "nitro/types.h"

extern u32 resultsState_020c0f80[2];
#define resultsWork ((int)resultsState_020c0f80[1])
extern u32 func_ov034_020bb578();

u32 PollResultsScreen_020bdc18(void)

{
  int result;
  u32 nextState;
  
  result = resultsWork;
  nextState = 0xffffffff;
  func_ov034_020bb578();
  if ((*(u16 *)(result + 6) & 0x4000) != 0) {
    nextState = 2;
  }
  return nextState;
}
