#include "nitro/types.h"

BOOL func_ov076_020c8b28(int work) {
  int offset;
  int total;
  int index;

  total = 0;
  index = 0;
  do {
    offset = index * 2;
    index = index + 1;
    total = total + (u32)*(u16 *)(work + offset + 0x49818);
  } while (index < 8);
  return total <= 100;
}
