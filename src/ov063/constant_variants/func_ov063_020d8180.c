#include "nitro/types.h"

extern unsigned int PXI_Init_020aafc4();

void func_ov063_020d8180(unsigned int unused,int entry,unsigned int value) {

  (*PXI_Init_020aafc4)(*(unsigned int *)(entry + 88),value);
}
