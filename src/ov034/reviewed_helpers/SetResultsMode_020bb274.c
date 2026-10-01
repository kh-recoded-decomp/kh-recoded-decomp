#include "nitro/types.h"

extern u32 resultsState_020c0f80[2];
#define resultsWork ((int)resultsState_020c0f80[1])

void SetResultsMode_020bb274(u32 mode)

{
  *(u32 *)(resultsWork + 0x6bc8) = mode;
  *(u32 *)(resultsWork + 0x6bb0) = 0;
  return;
}
