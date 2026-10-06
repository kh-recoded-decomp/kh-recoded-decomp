#include "nitro/types.h"

extern unsigned int DispatchSourceKindHandler();

void func_ov021_020ad078(unsigned int unused,int entry) {


  (*DispatchSourceKindHandler)(*(unsigned int *)(entry + 0x50));
}
