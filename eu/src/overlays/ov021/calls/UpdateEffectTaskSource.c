#include "nitro/types.h"

extern unsigned int UpdateEffectEntrySourceAdapter();

void UpdateEffectTaskSource(unsigned int unused,int entry,unsigned int value) {


  (*UpdateEffectEntrySourceAdapter)(*(unsigned int *)(entry + 0x50),value);
}
