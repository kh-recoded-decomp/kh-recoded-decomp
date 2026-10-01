#include "nitro/types.h"

extern u32 resultsState_020c0f80[2];
#define resultsWork ((int)resultsState_020c0f80[1])

void ClearResultsFlagTwo_020bde24(void)

{
  *(u16 *)(resultsWork + 6) = *(u16 *)(resultsWork + 6) & 0xfffd;
  return;
}
