#include "nitro/types.h"

extern unsigned char data_ov091_020c2bb4;
extern unsigned int data_ov091_020c3724;
extern unsigned int func_0204efa8();
extern unsigned int func_0204f00c();
extern unsigned int func_ov091_020bf950();

void func_ov091_020bf788(int work) {
  int index;
  u32 configuration [4];

  index = 0;
  configuration[0] = (*(int *)(work + 4) + 0x8000U & 0xfffffc) << 7 | 0x80000007;
  configuration[1] = 1;
  configuration[2] = 0;
  configuration[3] = 0;
  func_0204efa8(work + 0xf4,configuration);
  func_0204f00c(work + 0xf4,
                      (*(int *)(work + 0xc) + 0x8000U & 0xfffffc) << 7 | 0x80000000);
  do {
    func_ov091_020bf950(0,index,&data_ov091_020c2bb4 + index * 0x18,work);
    index = index + 1;
  } while (index < 6);
  configuration[0] = (*(int *)(work + 4) + 0x8000U & 0xfffffc) << 7 | 0x80000004;
  configuration[1] = 2;
  configuration[2] = 0;
  configuration[3] = 0;
  func_0204efa8(work + 0x6528,configuration);
  func_ov091_020bf950(1,0,&data_ov091_020c3724,work);
}
