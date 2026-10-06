#include "nitro/types.h"

extern u32 AddSessionCounter();
extern u32 AddToSelectionCounters_020c7564();
extern u32 func_ov077_020c7594();
extern u32 func_ov077_020c765c();
extern u32 func_ov077_020c7664();

void func_ov077_020c7678(u32 reward)

{
  switch(reward) {
  case 0xb7:
    AddToSelectionCounters_020c7564(0x1e);
    AddSessionCounter(5,1);
    func_ov077_020c7664(0xb2,0);
    return;
  case 0xb8:
    AddToSelectionCounters_020c7564(0x32);
    AddSessionCounter(5,1);
    func_ov077_020c7664(0xb3,0);
    return;
  case 0xbb:
    func_ov077_020c765c();
    AddSessionCounter(5,1);
    func_ov077_020c7664(0xb6,0);
    return;
  case 0xb9:
    func_ov077_020c7594(1);
    func_ov077_020c7664(0xb4,0);
    return;
  case 0xba:
    func_ov077_020c7594(2);
    func_ov077_020c7664(0xb5,0);
    return;
  case 0xbc:
    AddToSelectionCounters_020c7564(1000);
    func_ov077_020c765c();
    AddSessionCounter(5,1);
    func_ov077_020c7664(0xb7,0);
    return;
  case 0xbd:
    func_ov077_020c7594(4);
    AddToSelectionCounters_020c7564(1000);
    func_ov077_020c765c();
    AddSessionCounter(5,1);
    AddSessionCounter(0x12,1);
    func_ov077_020c7664(0xb8,0);
  }
  return;
}
