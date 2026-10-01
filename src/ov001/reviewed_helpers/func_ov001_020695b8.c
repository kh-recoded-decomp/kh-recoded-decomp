#include "nitro/types.h"

typedef unsigned int code();

extern unsigned int func_ov001_02067ed4();
extern unsigned int func_ov001_02069464();
extern unsigned int func_ov001_0206dc38();
extern unsigned int func_ov001_0206dc4c();

int func_ov001_020695b8(int work) {
  int result;
  unsigned int entry;

  *(u8 *)(work + 0x10) = 0;
  result = func_ov001_02067ed4();
  if (*(char *)(work + 0x12) != result) {
    return 0;
  }
  result = func_ov001_0206dc38();
  if (result <= 0) {
    return 0;
  }
  entry = func_ov001_0206dc4c(0);
  result = (**(code **)(work + 0x14))(work,entry);
  if (result != 0) {
    *(u8 *)(work + 0x10) = 1;
    result = func_ov001_02069464(work);
    if (result == 0) {
      return 0;
    }
  }
  return (int)*(char *)(work + 0x10);
}
