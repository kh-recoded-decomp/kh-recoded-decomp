#include "nitro/types.h"

extern u32 gGroupSceneGlobals[2];
#define resultsWork ((int)gGroupSceneGlobals[1])

void GroupSceneOnLeaveClearFlag2(void)

{
  *(u16 *)(resultsWork + 6) = *(u16 *)(resultsWork + 6) & 0xfffd;
  return;
}
