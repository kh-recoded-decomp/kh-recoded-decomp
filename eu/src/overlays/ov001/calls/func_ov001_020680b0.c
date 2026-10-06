#include "nitro/types.h"

extern unsigned int *data_ov001_020a048c;

u8 func_ov001_020680b0(int index) {
  int entry;

  entry = *(int *)(*data_ov001_020a048c + index * 4 + 8);
  if (entry == 0) {
    return 0xff;
  }
  return *(u8 *)(entry + 0x19);
}
