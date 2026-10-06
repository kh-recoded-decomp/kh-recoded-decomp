#include "nitro/types.h"

extern unsigned char data_ov086_020c2360;
extern unsigned int func_ov001_020645c8();

int func_ov086_020bf3b4(int group) {
  int flag;
  int countOrIndex;
  int baseIndex;
  int unlocked;
  int offsetOrIndex;

  baseIndex = 0;
  unlocked = 0;
  countOrIndex = 0;
  if (0 < group) {
    do {
      offsetOrIndex = countOrIndex * 4;
      countOrIndex = countOrIndex + 1;
      baseIndex = baseIndex + *(int *)(&data_ov086_020c2360 + offsetOrIndex);
    } while (countOrIndex < group);
  }
  offsetOrIndex = 0;
  countOrIndex = *(int *)(&data_ov086_020c2360 + group * 4);
  if (0 < countOrIndex) {
    do {
      flag = func_ov001_020645c8(baseIndex + offsetOrIndex + 0x581);
      offsetOrIndex = offsetOrIndex + 1;
      if (flag != 0) {
        unlocked = unlocked + 1;
      }
    } while (offsetOrIndex < countOrIndex);
  }
  return unlocked;
}
