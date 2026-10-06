#include "nitro/types.h"

extern u32 StopAndClearSoundEmitter();

void func_ov064_020d86d4(u32 event,int actor) {
  if (*(int *)(actor + 100) != -1) {
    StopAndClearSoundEmitter
              ((int)*(short *)(actor + 0x5c),*(int *)(actor + 100));
    *(u32 *)(actor + 100) = 0xffffffff;
  }
}
