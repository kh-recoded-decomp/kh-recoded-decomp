#include "nitro/types.h"

extern u32 func_0204d924();
extern u32 func_ov039_020bc618();
extern u32 func_ov089_020bfb8c();
extern u32 func_ov089_020bfdac();

void func_ov089_020c040c(void) {
  int work;

  work = func_ov039_020bc618();
  if (*(int *)(work + 0x73c) != 0) {
    return;
  }
  if (*(int *)(work + 0x904) != 0) {
    func_ov089_020bfb8c(work,0);
    return;
  }
  func_0204d924(0,1);
  func_ov089_020bfdac(work,1);
}
