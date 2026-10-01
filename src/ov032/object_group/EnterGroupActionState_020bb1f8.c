#include "nitro/types.h"

extern int contextData_020c0060[];
#define activeContext_020c0064 contextData_020c0060[1]
extern u32 func_ov001_02066810();
extern u32 func_ov001_02087628();

u32 EnterGroupActionState_020bb1f8(void)

{
  int group;
  
  group = activeContext_020c0064;
  *(u16 *)(activeContext_020c0064 + 6) = *(u16 *)(activeContext_020c0064 + 6) | 0x20;
  if ((*(u16 *)(group + 6) & 0x10) == 0) {
    func_ov001_02066810();
    func_ov001_02087628(1);
  }
  return 0xe;
}
