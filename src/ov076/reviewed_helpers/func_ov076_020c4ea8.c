#include "nitro/types.h"

extern unsigned int func_ov039_020bc1bc();
extern unsigned int func_ov076_020c827c();
extern unsigned int func_ov076_020ccd30();

void func_ov076_020c4ea8(unsigned int *work) {
  unsigned int scene;

  *work = 1;
  work[0x71bd] = 0;
  func_ov076_020c827c(work);
  if (work[0x1281d] != 0) {
    work[0x1281d] = 0;
    return;
  }
  scene = func_ov039_020bc1bc();
  func_ov076_020ccd30(scene,1);
}
