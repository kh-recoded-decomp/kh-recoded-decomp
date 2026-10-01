#include "nitro/types.h"

extern u32 data_ov021_020b5604;
extern u32 data_ov021_020b51e0;
extern u32 Msg_OpenContainerAndReadHeader_0202cc6c();

void func_ov021_020a7c90(void) {
  data_ov021_020b5604 = Msg_OpenContainerAndReadHeader_0202cc6c(&data_ov021_020b51e0,0x11,0);
}
