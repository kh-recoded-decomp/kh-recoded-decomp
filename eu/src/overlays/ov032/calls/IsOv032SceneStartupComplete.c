#include "nitro/types.h"

#define false 0
#define true 1
extern int data_ov032_020c0080[2];
#define resultsWork data_ov032_020c0080[1]

BOOL IsOv032SceneStartupComplete(void)

{
  if (resultsWork == 0) {
    return false;
  }
  return (*(u16 *)(resultsWork + 6) & 1) == 0;
}
