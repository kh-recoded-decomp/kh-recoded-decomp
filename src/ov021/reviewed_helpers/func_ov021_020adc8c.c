#include "nitro/types.h"

extern unsigned int PXI_Init_020ae720();

void func_ov021_020adc8c(unsigned int unused,int entry) {


  (*PXI_Init_020ae720)(*(unsigned int *)(entry + 0x50));
}
