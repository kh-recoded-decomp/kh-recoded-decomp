#include "nitro/types.h"

extern u32 func_ov001_02063a80();
extern u32 func_ov075_020ce700();
extern u32 func_ov075_020ce730();
extern u32 func_ov075_020ce7f8();
extern u32 func_ov075_020ce800();

void ApplyDialogReward_020ce814(u32 reward)

{
  switch(reward) {
  case 0xb7:
    func_ov075_020ce700(0x1e);
    func_ov001_02063a80(5,1);
    func_ov075_020ce800(0xb2,0);
    return;
  case 0xb8:
    func_ov075_020ce700(0x32);
    func_ov001_02063a80(5,1);
    func_ov075_020ce800(0xb3,0);
    return;
  case 0xbb:
    func_ov075_020ce7f8();
    func_ov001_02063a80(5,1);
    func_ov075_020ce800(0xb6,0);
    return;
  case 0xb9:
    func_ov075_020ce730(1);
    func_ov075_020ce800(0xb4,0);
    return;
  case 0xba:
    func_ov075_020ce730(2);
    func_ov075_020ce800(0xb5,0);
    return;
  case 0xbc:
    func_ov075_020ce700(1000);
    func_ov075_020ce7f8();
    func_ov001_02063a80(5,1);
    func_ov075_020ce800(0xb7,0);
    return;
  case 0xbd:
    func_ov075_020ce730(4);
    func_ov075_020ce700(1000);
    func_ov075_020ce7f8();
    func_ov001_02063a80(5,1);
    func_ov001_02063a80(0x12,1);
    func_ov075_020ce800(0xb8,0);
  }
  return;
}
