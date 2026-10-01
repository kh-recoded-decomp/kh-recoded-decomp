#include "nitro/types.h"

extern unsigned char data_ov103_020c05e8;
extern unsigned int InitObjManager_0204efa8();
extern unsigned int func_ov103_020bf6b0();

void func_ov103_020bf5c8(int work) {
  int index;
  u32 configuration [4];

  index = 0;
  configuration[0] = (*(int *)(work + 0x10) + 0x8000U & 0xfffffc) << 7 | 0x8000000d;
  configuration[1] = 1;
  configuration[2] = 0;
  configuration[3] = 0;
  InitObjManager_0204efa8(work + 0x174,configuration);
  do {
    func_ov103_020bf6b0(0,index,&data_ov103_020c05e8 + index * 0x14,work);
    index = index + 1;
  } while (index < 0xc);
}
