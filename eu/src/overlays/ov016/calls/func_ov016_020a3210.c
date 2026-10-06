#include "nitro/types.h"

extern unsigned int func_ov001_02086384();
extern unsigned int IsNodeFlagBitClear();
extern unsigned int func_ov016_020a229c();

void func_ov016_020a3210(int owner) {
  int entry;
  int active;
  u32 flags;
  int index;

  entry = *(int *)(owner + 4);
  index = 0;
  if (index < (int)(u32)*(u16 *)(entry + 0x3e)) {
    do {
      entry = func_ov001_02086384(entry,index);
      active = IsNodeFlagBitClear();
      if (active != 0) {
        if (*(int *)(entry + 0x3c) + 0x1800 < 0x80) {
          func_ov016_020a229c(entry,0);
          flags = *(u32 *)(entry + 0xc0) | 0x1000000;
        }
        else {
          func_ov016_020a229c(entry,1);
          flags = *(u32 *)(entry + 0xc0) & 0xfeffffff;
        }
        *(u32 *)(entry + 0xc0) = flags;
      }
      entry = *(int *)(owner + 4);
      index = index + 1;
    } while (index < (int)(u32)*(u16 *)(entry + 0x3e));
  }
}
