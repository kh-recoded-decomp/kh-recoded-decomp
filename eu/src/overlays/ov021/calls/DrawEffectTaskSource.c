#include "nitro/types.h"

extern unsigned int DrawEffectEntrySourceAdapter();

void DrawEffectTaskSource(unsigned int unused,int entry) {


  (*DrawEffectEntrySourceAdapter)(*(unsigned int *)(entry + 0x50));
}
