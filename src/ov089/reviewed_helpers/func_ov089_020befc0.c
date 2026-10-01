#include "nitro/types.h"

extern u32 func_ov039_020bc618();
extern u32 func_ov089_020bef34();

void func_ov089_020befc0(u32 event,u32 buttons) {
  int work;

  work = func_ov039_020bc618();
  if (*(int *)(work + 0x8fc) == 0) {
    return;
  }
  if ((buttons & 0xf0) == 0) {
    return;
  }
  func_ov089_020bef34(work,event,1);
}
