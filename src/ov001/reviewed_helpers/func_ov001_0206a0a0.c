#include "nitro/types.h"

extern unsigned int *data_ov001_020a0480;
extern unsigned int data_ov001_0209eb00;
extern unsigned int LoadCenteredScreenSprite_0206a860();
extern unsigned int Msg_OpenContainerAndReadHeader_0202cc6c();
extern unsigned int NNSi_FndGetCurrentRootHeap_0202a764();
extern unsigned int func_01ff8740();

unsigned int func_ov001_0206a0a0(int *initialValues) {
  void *resource;
  int variant;

  variant = *initialValues;
  data_ov001_020a0480 = NNSi_FndGetCurrentRootHeap_0202a764();
  func_01ff8740(0,data_ov001_020a0480,0x68);
  *data_ov001_020a0480 = 0;
  data_ov001_020a0480[6] = 0x1f000;
  data_ov001_020a0480[1] = 0x2000;
  *(u8 *)(data_ov001_020a0480 + 0x19) = 0;
  data_ov001_020a0480[10] = 0;
  data_ov001_020a0480[0xb] = 0;
  data_ov001_020a0480[7] = 0x1800;
  *(u8 *)((int)data_ov001_020a0480 + 0x66) = *(u8 *)((int)data_ov001_020a0480 + 0x66) & ~1U;
  resource = Msg_OpenContainerAndReadHeader_0202cc6c(&data_ov001_0209eb00,2,0);
  data_ov001_020a0480[0x18] = resource;
  LoadCenteredScreenSprite_0206a860(variant);
  return 0x206a139;
}
