#include "nitro/types.h"

extern unsigned int PXI_Init_020aafe4();

void func_ov063_020d8198(unsigned int unused,int entry) {

  (*PXI_Init_020aafe4)(*(unsigned int *)(entry + 88));
}
