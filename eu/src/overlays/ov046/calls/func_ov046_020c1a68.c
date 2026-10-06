#include "nitro/types.h"

extern unsigned int data_ov046_020c3500;
extern unsigned char data_ov046_020c33d4;

int func_ov046_020c1a68(int index) {
  int value;

  value = *(int *)(&data_ov046_020c33d4 + index * 0xc);
  if ((*(u32 *)(data_ov046_020c3500 + 0xf0) & 0x80000) != 0) {
    value = value + 0x2000;
  }
  return value;
}
