#include "nitro/types.h"

#define false 0
#define true 1
extern int resultsState_020c0f80[2];
#define resultsWork resultsState_020c0f80[1]

BOOL IsResultsInputEnabled_020bde08(void)

{
  if (resultsWork == 0) {
    return false;
  }
  return (*(u16 *)(resultsWork + 6) & 1) == 0;
}
