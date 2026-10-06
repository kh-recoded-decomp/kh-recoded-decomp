#include "nitro/types.h"

extern u32 LoadOv038MsgContainers();
extern u32 LoadOv038Graphics();
extern u32 InitOv038SpriteManagers();
extern u32 ResetOv038ExitState();

void func_ov038_020bbcbc(void) {
  LoadOv038MsgContainers();
  LoadOv038Graphics();
  InitOv038SpriteManagers();
  ResetOv038ExitState(1);
}
