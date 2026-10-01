#include "nitro/types.h"

extern u32 resultsState_020c0060[2];
#define resultsWork ((int)resultsState_020c0060[1])

void func_ov032_020bb47c(void)

{
  *(u16 *)(resultsWork + 6) = *(u16 *)(resultsWork + 6) & 0xfffd;
  return;
}
