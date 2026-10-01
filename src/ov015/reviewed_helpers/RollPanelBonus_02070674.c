#include "nitro/types.h"

#define false 0
#define true 1
extern u32 func_0202a9d0();
extern u32 func_ov002_02066c78();

BOOL RollPanelBonus_02070674(void)

{
  u32 roll;
  int count;
  int blocked;
  
  roll = func_0202a9d0(100);
  count = func_ov002_02066c78(8,0,0,0);
  blocked = func_ov002_02066c78(5,0,0,0);
  if (blocked != 0) {
    return false;
  }
  if ((count >= 0x50) && ((int)roll < 0x18)) {
    return true;
  }
  if ((count >= 0x32) && ((int)roll < 6)) {
    return true;
  }
  return (int)roll < 1;
}
