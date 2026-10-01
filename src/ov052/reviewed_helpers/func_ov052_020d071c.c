#include "nitro/types.h"

extern unsigned int func_01fffe7c();
extern unsigned int ClearSbcCallback_020188b8();
extern unsigned int RegisterSbcCallback_020188a4();

void func_ov052_020d071c(int actor) {
  *(int *)(*(int *)(actor + 0x230) + 0x50) = actor;
  ClearSbcCallback_020188b8((void *)(*(int *)(actor + 0x230) + 0x24));
  RegisterSbcCallback_020188a4(*(int *)(actor + 0x230) + 0x24,func_01fffe7c,0,6,3);
}
