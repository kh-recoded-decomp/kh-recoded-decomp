#include "nitro/types.h"

extern unsigned int PXI_Init_020ae718();

void func_ov021_020adc80(unsigned int unused,int entry,unsigned int value) {


  (*PXI_Init_020ae718)(*(unsigned int *)(entry + 0x50),value);
}
