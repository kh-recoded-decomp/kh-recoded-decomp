#include "nitro/types.h"

extern u32 data_ov021_020b5624;
extern u32 sOv021_BaChSeP2_020b5200;
extern u32 Msg_OpenContainerAndReadHeader();

void func_ov021_020a7cb0(void) {
  data_ov021_020b5624 = Msg_OpenContainerAndReadHeader(&sOv021_BaChSeP2_020b5200,0x11,0);
}
