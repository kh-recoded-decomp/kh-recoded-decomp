#include "nitro/types.h"

extern unsigned int ResetEntryStates();

void func_ov063_020d81b8(unsigned int unused,int entry) {

  (*ResetEntryStates)(*(unsigned int *)(entry + 88));
}
