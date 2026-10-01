#include "nitro/types.h"

extern u16 data_02060500;
extern unsigned int func_0204d924();

void func_ov084_020bfbc4(u8 *selection) {
  do {
    *selection = *selection + 1;
    if ((u32)*selection >= 2) {
      if ((data_02060500 & 0x80) == 0) {
        *selection = 1;
        return;
      }
      *selection = 0;
    }
  } while ((1 << *selection & (u32)selection[1]) == 0);
  func_0204d924(0,0);
  selection[2] = 1;
}
