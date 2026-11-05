#include "nitro/types.h"

extern unsigned int GetEntryPoolObjectAtIndex();

int FindLastInactiveObjectInParentChain(int entry) {
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
    entry = GetEntryPoolObjectAtIndex(*(unsigned int *)(entry + 4));
  }
  return selected;
}
