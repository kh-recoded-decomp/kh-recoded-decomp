#include "nitro/types.h"

extern unsigned int data_ov035_020bc4e0;
extern unsigned int func_ov035_020badf0();

int func_ov035_020bb2a0(void) {
  int state;
  int index;
  int count;

  count = 0;
  index = 0;
  if (index < (int)(u32)*(u8 *)(data_ov035_020bc4e0 + 0x42)) {
    do {
      state = func_ov035_020badf0(index);
      if (state == 0) {
        count = count + 1;
      }
      index = index + 1;
    } while (index < (int)(u32)*(u8 *)(data_ov035_020bc4e0 + 0x42));
  }
  return count;
}
