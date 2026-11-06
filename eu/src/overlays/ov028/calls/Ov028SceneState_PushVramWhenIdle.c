#include "nitro/types.h"

extern u32 gOv028FieldSceneWorkStorage;
extern u32 PushVramState();
extern u32 func_ov001_02063620();

u32 Ov028SceneState_PushVramWhenIdle(void) {
  u32 busy;

  busy = func_ov001_02063620();
  if (busy == 0) {
    PushVramState();
    *(u16 *)(gOv028FieldSceneWorkStorage + 6) = *(u16 *)(gOv028FieldSceneWorkStorage + 6) | 0x8000;
    return 1;
  }
  return 0xffffffff;
}
