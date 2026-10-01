#include "nitro/types.h"

extern unsigned char data_ov002_0206ae24;

unsigned int func_ov002_0206a9f8(int value) {
  int index;

  index = 0;
  do {
    if (value == *(int *)(&data_ov002_0206ae24 + index * 4)) {
      return 0;
    }
    index = index + 1;
  } while (index < 0x13);
  return 1;
}
