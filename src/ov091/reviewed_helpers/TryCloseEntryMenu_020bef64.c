#include "nitro/types.h"

extern u32 func_0204d924();
extern u32 func_ov039_020bbf78();
extern u32 func_ov039_020bc8a0();
extern u32 func_ov091_020c1754();

void TryCloseEntryMenu_020bef64(void)

{
  int result;
  
  result = func_ov091_020c1754();
  if (result != 0) {
    return;
  }
  func_ov039_020bc8a0();
  func_ov039_020bbf78(0,0xffffffff,1);
  func_0204d924(0,3);
  return;
}
