#include "nitro/types.h"

extern u32 data_ov036_020c3844;
extern u32 data_ov036_020c38dc;
extern u32 data_ov036_020c38f4;
extern u32 func_02001458();

void func_ov036_020beb5c(void) {
  func_02001458(data_ov036_020c3844 + 0x644c,&data_ov036_020c38dc);
  func_02001458(data_ov036_020c3844 + 0x68a8,&data_ov036_020c38f4);
}
