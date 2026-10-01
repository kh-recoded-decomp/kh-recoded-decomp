#include "nitro/types.h"

extern u32 func_ov001_02063a80();
extern u32 func_ov075_020ca510();
extern u32 func_ov075_020ca540();
extern u32 func_ov075_020ca608();
extern u32 func_ov075_020ca610();

void func_ov076_020ca624(u32 reward)

{
  switch(reward) {
  case 0xb7:
    func_ov075_020ca510(0x1e);
    func_ov001_02063a80(5,1);
    func_ov075_020ca610(0xb2,0);
    return;
  case 0xb8:
    func_ov075_020ca510(0x32);
    func_ov001_02063a80(5,1);
    func_ov075_020ca610(0xb3,0);
    return;
  case 0xbb:
    func_ov075_020ca608();
    func_ov001_02063a80(5,1);
    func_ov075_020ca610(0xb6,0);
    return;
  case 0xb9:
    func_ov075_020ca540(1);
    func_ov075_020ca610(0xb4,0);
    return;
  case 0xba:
    func_ov075_020ca540(2);
    func_ov075_020ca610(0xb5,0);
    return;
  case 0xbc:
    func_ov075_020ca510(1000);
    func_ov075_020ca608();
    func_ov001_02063a80(5,1);
    func_ov075_020ca610(0xb7,0);
    return;
  case 0xbd:
    func_ov075_020ca540(4);
    func_ov075_020ca510(1000);
    func_ov075_020ca608();
    func_ov001_02063a80(5,1);
    func_ov001_02063a80(0x12,1);
    func_ov075_020ca610(0xb8,0);
  }
  return;
}
