#include "nitro/types.h"

extern u32 resultsState_020c0f80[2];
#define resultsWork ((int)resultsState_020c0f80[1])
extern u32 func_02027304();
extern u32 func_02027320();

void AdvanceResultsTransition_020bb234(int mode,int transition)

{
  int result;
  
  result = func_02027304(transition + 0xf50);
  if (result == 0) {
    func_02027320(transition + 0xf50);
    *(int *)(resultsWork + 0x6bd8) = mode + 1;
    *(u32 *)(resultsWork + 0x6bf8) = 0;
    *(u32 *)(resultsWork + 0x6bb0) = 0;
  }
  return;
}
