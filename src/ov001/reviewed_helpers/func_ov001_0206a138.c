#include "nitro/types.h"

extern unsigned int *data_ov001_020a0480;

unsigned int func_ov001_0206a138(void) {
  unsigned int callback;
  u32 flags;

  callback = 0;
  flags = *data_ov001_020a0480;
  if ((flags & 0x20) == 0) {
    if ((flags & 1) != 0) {
      return 0x206a185;
    }
    if ((flags & 2) != 0) {
      return 0x206a209;
    }
    if ((flags & 4) != 0) {
      return 0x206a291;
    }
    if ((flags & 8) != 0) {
      callback = 0x206a365;
    }
  }
  return callback;
}
