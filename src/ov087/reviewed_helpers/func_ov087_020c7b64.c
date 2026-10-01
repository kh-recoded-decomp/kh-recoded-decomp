#include "nitro/types.h"

extern u32 func_0204d924();
extern u32 func_ov001_020647a4();
extern u32 func_ov001_02064810();
extern u32 func_ov001_02064828();
extern u32 func_ov001_02064998();
extern u32 func_ov033_020baa4c();
extern u32 func_ov039_020bbf78();
extern u32 func_ov039_020bc618();

void func_ov087_020c7b64(void) {
  int menu;
  u32 selection;

  menu = func_ov039_020bc618();
  selection = *(u32 *)(*(int *)(menu + 4) * 0x108 + menu + 0x118);
  if (*(int *)(menu + 0x10) == 0) {
    switch(*(u32 *)(menu + 0xbc0)) {
    case 0:
      func_ov001_02064998();
      break;
    case 1:
      func_ov001_020647a4(selection,*(u32 *)(menu + 0xbc4));
      break;
    case 2:
      func_ov001_02064810();
      break;
    case 3:
      func_ov001_02064828(selection,*(u32 *)(menu + 0xbc4));
    }
    func_ov033_020baa4c();
    func_ov039_020bbf78(0xffffffff,0xffffffff,1);
    func_0204d924(0,1);
    return;
  }
}
