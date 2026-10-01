#include "nitro/types.h"

extern unsigned int func_ov001_0207f018();
extern unsigned int func_ov001_0207f028();
extern unsigned int func_ov001_0207f038();
extern unsigned int func_ov001_020822ac();

void func_ov001_020828ac(void) {
  int count;
  int actor;
  u32 entry;
  u32 index;

  count = func_ov001_0207f018();
  index = 0;
  if (0 < count) {
    do {
      actor = func_ov001_0207f028(index);
      if (((actor != 0) && (*(unsigned short *)(actor + 0x46) != 0)) &&
         (entry = func_ov001_0207f038(index,0), *(unsigned char *)(*(int *)(entry + 8) + 0x7d) == '\v')) {
        func_ov001_020822ac(actor);
        return;
      }
      index = index + 1;
    } while ((int)index < count);
  }
}
