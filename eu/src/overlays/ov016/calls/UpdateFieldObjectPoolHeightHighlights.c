#include "nitro/types.h"

extern unsigned int GetEntryPoolObjectAtIndex();
extern unsigned int IsNodeFlagBitClear();
extern unsigned int UpdateFieldObjectHighlight();

void UpdateFieldObjectPoolHeightHighlights(int owner) {
  int entry;
  int active;
  u32 flags;
  int index;

  entry = *(int *)(owner + 4);
  index = 0;
  if (index < (int)(u32)*(u16 *)(entry + 0x3e)) {
    do {
      entry = GetEntryPoolObjectAtIndex(entry,index);
      active = IsNodeFlagBitClear();
      if (active != 0) {
        if (*(int *)(entry + 0x3c) + 0x1800 < 0x80) {
          UpdateFieldObjectHighlight(entry,0);
          flags = *(u32 *)(entry + 0xc0) | 0x1000000;
        }
        else {
          UpdateFieldObjectHighlight(entry,1);
          flags = *(u32 *)(entry + 0xc0) & 0xfeffffff;
        }
        *(u32 *)(entry + 0xc0) = flags;
      }
      entry = *(int *)(owner + 4);
      index = index + 1;
    } while (index < (int)(u32)*(u16 *)(entry + 0x3e));
  }
}
