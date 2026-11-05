#include "nitro/types.h"

extern unsigned int DispatchSourceKindHandler();

void DispatchEffectTaskSourceKind(unsigned int unused,int entry) {


  (*DispatchSourceKindHandler)(*(unsigned int *)(entry + 0x50));
}
