#include "nitro/types.h"

extern struct { int reserved; int context; } menuState_020c0068;
#define activeMenu menuState_020c0068.context
extern u32 func_ov001_0207187c();
extern u32 func_ov032_020bb8f4();
extern u32 func_ov032_020bb9e0();

u32 UpdateGroupMenuCounter_020bbb4c(void)

{
  int menu;
  int ready;
  
  menu = activeMenu;
  if (*(int *)(activeMenu + 0x18) == 100) {
    func_ov032_020bb8f4(activeMenu);
  }
  if ((*(int *)(menu + 0x20) != *(int *)(menu + 0x24)) &&
     (ready = func_ov001_0207187c(), ready != 0)) {
    func_ov032_020bb9e0(menu);
  }
  return 0;
}
