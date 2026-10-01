#include "nitro/types.h"

extern unsigned int PXI_Init_020aafd4();

void func_ov063_020d818c(unsigned int unused,int entry) {

  (*PXI_Init_020aafd4)(*(unsigned int *)(entry + 88));
}
