#include "nitro/types.h"

extern struct { int reserved; int context; } groupState_020c0060;
#define activeGroup groupState_020c0060.context
extern u32 func_ov001_0206685c();
extern u32 func_ov001_0206a7c0();
extern u32 func_ov001_0206a814();

u32 TryOpenGroupAction_020bb220(void)

{
  int state;
  int ready;
  
  state = activeGroup;
  if (((*(u16 *)(activeGroup + 6) & 0x10) == 0) &&
     (ready = func_ov001_0206685c(), ready != 0)) {
    return 0xffffffff;
  }
  ready = func_ov001_0206a814();
  if (ready == 0) {
    return 0xffffffff;
  }
  func_ov001_0206a7c0((int)*(char *)(state + 8));
  return 0xf;
}
