#include "nitro/types.h"

#define false 0
#define true 1
extern int resultsState_020c0060[2];
#define resultsWork resultsState_020c0060[1]

BOOL func_ov032_020bb460(void)

{
  if (resultsWork == 0) {
    return false;
  }
  return (*(u16 *)(resultsWork + 6) & 1) == 0;
}
