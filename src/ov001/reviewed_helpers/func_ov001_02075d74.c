#include "nitro/types.h"

extern unsigned char data_ov001_0209ee52;
extern unsigned char data_ov001_0209ee5e;
extern unsigned int GFXi_EnqueueCommand_02014090();

void func_ov001_02075d74(int work,int alternate) {
  if (alternate != 0) {
    GFXi_EnqueueCommand_02014090
              ((void *)0xf,0x30,(int)(&data_ov001_0209ee5e + *(int *)(work + 0x104) * 6),6);
    return;
  }
  GFXi_EnqueueCommand_02014090
            ((void *)0xf,0x30,(int)(&data_ov001_0209ee52 + *(int *)(work + 0x104) * 6),6);
}
