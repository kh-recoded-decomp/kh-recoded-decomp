#include "nitro/types.h"

extern unsigned int data_ov046_020c34e0;
extern unsigned char data_ov046_020c33b4;

int func_ov046_020c1a48(int index) {
  int value;

  value = *(int *)(&data_ov046_020c33b4 + index * 0xc);
  if ((*(u32 *)(data_ov046_020c34e0 + 0xf0) & 0x80000) != 0) {
    value = value + 0x2000;
  }
  return value;
}
