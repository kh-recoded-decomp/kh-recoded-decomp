#include "nitro/types.h"

extern unsigned char data_ov001_0209ee72;
extern unsigned char data_ov001_0209ee7e;
extern unsigned int NNS_GfdRegisterNewVramTransferTask();

void func_ov001_02075d74(int work,int alternate) {
  if (alternate != 0) {
    NNS_GfdRegisterNewVramTransferTask
              ((void *)0xf,0x30,(int)(&data_ov001_0209ee7e + *(int *)(work + 0x104) * 6),6);
    return;
  }
  NNS_GfdRegisterNewVramTransferTask
            ((void *)0xf,0x30,(int)(&data_ov001_0209ee72 + *(int *)(work + 0x104) * 6),6);
}
