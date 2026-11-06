#include "nitro/types.h"

extern u32 gOv028FieldSceneWorkStorage;
extern u32 BeginScreenFadeOut();
extern u32 IsScreenModeIdle();
extern u32 HasActiveFieldEffects();

u32 Ov028SceneState_BeginFadeOutWhenIdle(void) {
  int work;
  u32 busy;
  int idle;

  work = gOv028FieldSceneWorkStorage;
  if (((*(u16 *)(gOv028FieldSceneWorkStorage + 6) & 0x10) == 0) &&
     (busy = HasActiveFieldEffects(), busy != 0)) {
    return 0xffffffff;
  }
  idle = IsScreenModeIdle();
  if (idle != 0) {
    BeginScreenFadeOut((int)*(char *)(work + 8));
    return 0x10;
  }
  return 0xffffffff;
}
