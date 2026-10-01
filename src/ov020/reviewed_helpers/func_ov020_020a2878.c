#include "nitro/types.h"

extern unsigned int func_ov001_0208635c();

int func_ov020_020a2878(int entry) {
  int selected;

  selected = 0;
  while( TRUE ) {
    if ((*(u16 *)(entry + 0x54) & 0x8000) == 0) {
      selected = entry;
    }
    if (*(short *)(entry + 0x56) < 0) break;
    entry = func_ov001_0208635c(*(unsigned int *)(entry + 4));
  }
  return selected;
}
