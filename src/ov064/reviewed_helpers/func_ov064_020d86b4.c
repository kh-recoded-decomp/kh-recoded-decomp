#include "nitro/types.h"

extern u32 StopAndClearSoundEmitter_020a8e14();

void func_ov064_020d86b4(u32 event,int actor) {
  if (*(int *)(actor + 100) != -1) {
    StopAndClearSoundEmitter_020a8e14
              ((int)*(short *)(actor + 0x5c),*(int *)(actor + 100));
    *(u32 *)(actor + 100) = 0xffffffff;
  }
}
