#include "nitro/types.h"

extern struct { int reserved; int context; } groupState_020c0060;
#define activeGroup groupState_020c0060.context
extern u32 func_0202a778();
extern u32 func_ov001_0207b688();

u32 CompleteGroupTransition_020baad0(void)

{
  int ready;
  
  ready = func_ov001_0207b688();
  if (ready == 0) {
    return 0xffffffff;
  }
  if ((*(u16 *)(activeGroup + 6) & 1) != 0) {
    *(u16 *)(activeGroup + 6) = *(u16 *)(activeGroup + 6) & 0xfffe;
  }
  func_0202a778(0);
  return 7;
}
