#include "nitro/types.h"

extern u32 AddSessionCounter();
extern u32 AddToSelectionCounters_020ca530();
extern u32 func_ov076_020ca560();
extern u32 func_ov076_020ca628();
extern u32 func_ov076_020ca630();

void func_ov076_020ca644(u32 reward)

{
  switch(reward) {
  case 0xb7:
    AddToSelectionCounters_020ca530(0x1e);
    AddSessionCounter(5,1);
    func_ov076_020ca630(0xb2,0);
    return;
  case 0xb8:
    AddToSelectionCounters_020ca530(0x32);
    AddSessionCounter(5,1);
    func_ov076_020ca630(0xb3,0);
    return;
  case 0xbb:
    func_ov076_020ca628();
    AddSessionCounter(5,1);
    func_ov076_020ca630(0xb6,0);
    return;
  case 0xb9:
    func_ov076_020ca560(1);
    func_ov076_020ca630(0xb4,0);
    return;
  case 0xba:
    func_ov076_020ca560(2);
    func_ov076_020ca630(0xb5,0);
    return;
  case 0xbc:
    AddToSelectionCounters_020ca530(1000);
    func_ov076_020ca628();
    AddSessionCounter(5,1);
    func_ov076_020ca630(0xb7,0);
    return;
  case 0xbd:
    func_ov076_020ca560(4);
    AddToSelectionCounters_020ca530(1000);
    func_ov076_020ca628();
    AddSessionCounter(5,1);
    AddSessionCounter(0x12,1);
    func_ov076_020ca630(0xb8,0);
  }
  return;
}
