#include "nitro/types.h"

extern unsigned int data_ov046_020c34e0;
extern unsigned int data_ov046_020c33a0;
extern unsigned int Obj_FreeDataBuffers_02034ff0();
extern unsigned int func_02029f98();

void func_ov046_020c09fc(void) {
  Obj_FreeDataBuffers_02034ff0((void *)(data_ov046_020c34e0 + 0xf8));
  func_02029f98(0,((int *)&data_ov046_020c33a0)[*(int *)(data_ov046_020c34e0 + 0x80)]);
}
