#include "nitro/types.h"

extern unsigned int func_ov001_0207f040();
extern unsigned int func_ov001_0207f050();
extern unsigned int func_ov001_0207f060();
extern unsigned int ReleaseAttachedModels();

void func_ov001_020828d4(void) {
  int count;
  int actor;
  u32 entry;
  u32 index;

  count = func_ov001_0207f040();
  index = 0;
  if (0 < count) {
    do {
      actor = func_ov001_0207f050(index);
      if (((actor != 0) && (*(unsigned short *)(actor + 0x46) != 0)) &&
         (entry = func_ov001_0207f060(index,0), *(unsigned char *)(*(int *)(entry + 8) + 0x7d) == '\v')) {
        ReleaseAttachedModels(actor);
        return;
      }
      index = index + 1;
    } while ((int)index < count);
  }
}
