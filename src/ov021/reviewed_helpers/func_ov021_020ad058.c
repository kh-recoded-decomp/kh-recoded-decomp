#include "nitro/types.h"

extern unsigned int PXI_Init_020d7d54();

void func_ov021_020ad058(unsigned int unused,int entry) {


  (*PXI_Init_020d7d54)(*(unsigned int *)(entry + 0x50));
}
