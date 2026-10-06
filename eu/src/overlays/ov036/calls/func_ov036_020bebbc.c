#include "nitro/types.h"

extern u32 gTextWindowResourceTable;
extern u32 FreeResourceBufferAndProbeHeap();

void func_ov036_020bebbc(void) {
  FreeResourceBufferAndProbeHeap(gTextWindowResourceTable + 0x68a8);
  FreeResourceBufferAndProbeHeap(gTextWindowResourceTable + 0x644c);
}
