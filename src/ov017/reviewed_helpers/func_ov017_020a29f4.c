#include "nitro/types.h"

extern unsigned int ActorSlot_SetFlag8ByIndex_02036120();
extern unsigned int ActorSlot_UnlinkByIndex_02035c28();
extern unsigned int CacheEntry_SetActive_02087258();
extern unsigned int func_020bd6ec();
extern unsigned int func_ov042_020bd290();
extern unsigned int func_ov042_020bd590();

unsigned int func_ov017_020a29f4(void *work) {
  u32 flags;
  int *origin;
  int *extent;

  flags = func_020bd6ec();
  if ((flags & 1) == 0) {
    origin = (int *)func_ov042_020bd290();
    extent = (int *)func_ov042_020bd590();
    if (*(int *)((int)work + 0x38) - *origin < *extent * 3) {
      ActorSlot_SetFlag8ByIndex_02036120((u32)*(u8 *)((int)work + 0x32),0);
      ActorSlot_UnlinkByIndex_02035c28((u32)*(u8 *)((int)work + 0x32));
      CacheEntry_SetActive_02087258(work,0);
    }
  }
  return 0;
}
