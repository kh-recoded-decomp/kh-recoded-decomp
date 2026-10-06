#include "nitro/types.h"

extern unsigned int data_ov046_020c3500;
extern unsigned int data_ov046_020c33c0;
extern unsigned int Obj_FreeDataBuffers();
extern unsigned int func_02029fac();

void func_ov046_020c0a1c(void) {
  Obj_FreeDataBuffers((void *)(data_ov046_020c3500 + 0xf8));
  func_02029fac(0,((int *)&data_ov046_020c33c0)[*(int *)(data_ov046_020c3500 + 0x80)]);
}
