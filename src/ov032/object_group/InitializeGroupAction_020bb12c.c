#include "nitro/types.h"

extern int contextData_020c0060[];
#define activeContext_020c0064 contextData_020c0060[1]
extern u32 func_ov001_0206a72c();
extern u32 func_ov032_020ba604();

u32 InitializeGroupAction_020bb12c(void)

{
  int group;
  
  group = activeContext_020c0064;
  func_ov001_0206a72c((int)*(char *)(activeContext_020c0064 + 8));
  *(u16 *)(group + 6) = *(u16 *)(group + 6) | 0x20;
  func_ov032_020ba604();
  return 10;
}
