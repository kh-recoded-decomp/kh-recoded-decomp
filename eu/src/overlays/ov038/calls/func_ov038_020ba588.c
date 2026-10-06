#include "nitro/types.h"

extern u32 OpenFieldMenuMode();
extern u32 func_ov038_020bbd08();

u32 func_ov038_020ba588(void) {
  int ready;

  ready = func_ov038_020bbd08();
  if (ready != 0) {
    OpenFieldMenuMode(2);
    return 4;
  }
  return 0xffffffff;
}
