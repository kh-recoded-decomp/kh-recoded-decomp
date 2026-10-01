#include "nitro/types.h"

extern u32 StartSubMode_020af260();

u32 func_ov021_020af248(int *arguments) {
  StartSubMode_020af260((void *)arguments[2],(void *)arguments[1],*arguments);
  return 0x20af365;
}
