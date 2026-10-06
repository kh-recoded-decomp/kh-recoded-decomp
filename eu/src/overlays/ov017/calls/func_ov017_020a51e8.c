#include "nitro/types.h"

extern unsigned int func_ov001_02086384();

int func_ov017_020a51e8(int entry) {
  BOOL excluded;
  int selected;

  selected = 0;
  while( TRUE ) {
    excluded = TRUE;
    if ((*(char *)(entry + 0x50) != '\x02') && (*(char *)(entry + 0x50) != '\x01')) {
      excluded = FALSE;
    }
    if (!excluded) {
      selected = entry;
    }
    if (*(short *)(entry + 0x56) < 0) break;
    entry = func_ov001_02086384(*(unsigned int *)(entry + 4));
  }
  return selected;
}
