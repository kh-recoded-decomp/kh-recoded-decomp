#include "nitro/types.h"

extern u32 data_ov032_020c0080[2];
#define resultsWork ((int)data_ov032_020c0080[1])

void func_ov032_020bb49c(void)

{
  *(u16 *)(resultsWork + 6) = *(u16 *)(resultsWork + 6) & 0xfffd;
  return;
}
