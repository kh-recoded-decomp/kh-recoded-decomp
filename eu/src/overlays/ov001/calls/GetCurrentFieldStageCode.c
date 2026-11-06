#include "nitro/types.h"

extern u32 gFieldSessionWork;

int GetCurrentFieldStageCode(void) {
  return (int)*(short *)(gFieldSessionWork + 0x208);
}
